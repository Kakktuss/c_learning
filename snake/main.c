#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "src/snake/snake.h"
#include "src/world/world.h"
#include "uv.h"
#include "src/world/world_event.h"
#include "src/snake/snake_event.h"
#include "src/utility.h"

FILE* file;
snake_t snake;
world_t  world;

direction_command_buffer_t direction_command_buffer;

uv_loop_t *loop;
uv_timer_t timer;
uv_tty_t tty_stdout;
uv_tty_t tty_stdin;
uv_timer_t timer_renderer;
uv_timer_t timer_mover;
uv_timer_t timer_apple_spawner;
uv_timer_t timer_obstacle_spawner;

/**
 * @brief Inits the snake with it's parts
 * 
 */
void init_snake() {
    coordinate_t headCoordinates = {.x = 1, .y = 1};
    coordinate_t wickCoordinates = { .x = 2, .y = 1 };
    coordinate_t wickBottomCoordinates = { .x = 2, .y = 2};
    snake_part_t head = create_snake_part_entity(headCoordinates);
    snake_part_t wick = create_snake_part_entity(wickCoordinates);
    snake_part_t wick_bottom = create_snake_part_entity(wickBottomCoordinates);

    snake_part_t parts[] = {head, wick, wick_bottom};

    snake = create_snake_entity(3, parts, DOWN);
}

void init_apples() {
    int world_canvas_cases_count = (world.height - 2) * (world.width - 2);

    int apples_random_limit = floor(world_canvas_cases_count / 6);

    world.apples_count = rand() % apples_random_limit;

    for(int i = 0; i < world.apples_count; i++) {
        coordinate_t apple_coordinates = {.x = rand() % (world.width - 2) + 1, .y = rand() % (world.height - 2) + 1 };

        apple_t apple = create_apple_entity(apple_coordinates);

        world.apples[i] = apple;
    }
}

void init_obstacle() {
    int world_canvas_cases_count = (world.height - 2) * (world.width - 2);

    int obstacles_random_limit = floor(world_canvas_cases_count / 6);

    world.obstacles_count = rand() % obstacles_random_limit;

    for(int i = 0; i < world.obstacles_count; i++) {
        coordinate_t obstacle_coordinates = {.x = rand() % (world.width - 2) + 1, .y = rand() % (world.height - 2) + 1 };

        obstacle_t obstacle = create_obstacle_entity(obstacle_coordinates);

        world.obstacles[i] = obstacle;
    }
}

/**
 * @brief Inits the world
 * 
 * @param file_name 
 */
bool init_world(char* file_name) {
    file = fopen(file_name, "r");

    if(file == NULL) {
        fprintf(stderr, "Error opening file: %s\n", strerror(errno));
        return false;
    }

    init_snake();

    world = create_world(file, &snake);

    init_apples();

    init_obstacle();

    return true;
}

/**
 * @brief Callback triggered by the timer renderer event
 * 
 * @param handle 
 */
void timer_renderer_cb(uv_timer_t* handle) {
    world_renderer_timer_handler(&tty_stdout, &world);
}

/**
 * @brief Callback triggered by the timer mover event
 * @param handle
 */
void timer_mover_cb(uv_timer_t* handle) {
    snake_mover_timer_handler(loop, &tty_stdout, &direction_command_buffer, &world, &snake);
}

void timer_apple_spawner_cb(uv_timer_t* handle) {

}

void timer_obstacle_spawner_cb(uv_timer_t* handle) {

}

/**
 * @brief Callback triggered by the stdin event to alloc the buffer
 * 
 * @param handle 
 * @param suggested_size 
 * @param buf 
 */
void stdin_alloc_buffer(uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf) {
    buf->base = malloc(suggested_size);
    buf->len = suggested_size;
}

/**
 * @brief Callback triggered by the stdin event to read the buffer
 * 
 * @param stream 
 * @param nread 
 * @param buf 
 */
void stdin_read_cb(uv_stream_t* stream, ssize_t nread, const uv_buf_t* buf) {
    world_stdin_handler(buf, &world, &snake, &direction_command_buffer);

    free(buf->base);
}

void init_loop() {
    loop = uv_default_loop();

    // Init the tty stdin handler on mode raw
    uv_tty_init(loop, &tty_stdin, 0, 1);
    uv_tty_set_mode(&tty_stdin, UV_TTY_MODE_RAW);
    uv_read_start((uv_stream_t*)&tty_stdin, stdin_alloc_buffer, stdin_read_cb);

    // Init the tty stdout
    uv_tty_init(loop, &tty_stdout, 1, 0);

    // Init the renderer timer on a second rendering basis
    uv_timer_init(loop, &timer_renderer);
    uv_timer_start(&timer_renderer, timer_renderer_cb, 0, 100);

    // Init the renderer timer delayed by 2.5 seconds and triggering every 1 second basis
    uv_timer_init(loop, &timer_mover);
    uv_timer_start(&timer_mover, timer_mover_cb, 2500, 500);

    // Init the apple spawner timer delayed by 2.5 seconds and triggering on a random basis
    uv_timer_init(loop, &timer_apple_spawner);
    uv_timer_start(&timer_apple_spawner, timer_apple_spawner_cb, 2500, 1000);

    // Init the obstacle spawner timer delayed by 2.5 seconds and triggering on a random basis
    uv_timer_init(loop, &timer_obstacle_spawner);
    uv_timer_start(&timer_obstacle_spawner, timer_obstacle_spawner_cb, 2500, 1000);
}

int main(int argc, char **argv) {
    char *fileName = NULL;
    if (argc > 1) {
        fileName = argv[1];
    } else {
        printf("Enter at least the world file\n");
        return -1;
    }

    if(!init_world(fileName))
    {
        printf("Unable to init the world");
        return -1;
    }

    init_loop();

    uv_run(loop, UV_RUN_DEFAULT);

    return 0;
}