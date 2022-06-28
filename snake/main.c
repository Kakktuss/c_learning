#include <stdio.h>
#include <uv.h>
#include <stdlib.h>
#include <stdbool.h>
#include "world/world.h"
#include "loop/event.h"

FILE* file;
snake_t snake;
world_t  world;
apple_t* apples;
size_t apples_count;
obstacle_t* obstacles;
size_t obstacles_count;

uv_loop_t *loop;
uv_timer_t timer;
uv_tty_t tty_stdout;
uv_tty_t tty_stdin;
uv_timer_t timer_renderer;
uv_timer_t timer_mover;

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

    int apples_random_limit = world_canvas_cases_count % 100;

    apples_count = rand() % apples_random_limit;

    /**
     * for(int i = 0; i < apples_count; i++) {
        coordinate_t apple_coordinates = {.x = rand() % (world.width - 2), .y = rand() % (world.height % 2) };

        apple_t apple = create_apple_entity(apple_coordinates);

        apples[i] = apple;
    }
     */
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

    world = create_world(file, &snake, &apples, apples_count, &obstacles, obstacles_count);

    init_apples();

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
    snake_mover_timer_handler(loop, &tty_stdout, &world, &snake);
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
    world_stdin_handler(buf, &world, &snake);

    free(buf->base);
}

void init_loop() {
    loop = uv_default_loop();

    uv_tty_init(loop, &tty_stdin, 0, 1);
    uv_tty_init(loop, &tty_stdout, 1, 0);
    uv_tty_set_mode(&tty_stdin, UV_TTY_MODE_RAW);

    uv_read_start((uv_stream_t*)&tty_stdin, stdin_alloc_buffer, stdin_read_cb);

    uv_timer_init(loop, &timer_renderer);
    uv_timer_start(&timer_renderer, timer_renderer_cb, 0, 1000);

    uv_timer_init(loop, &timer_mover);
    uv_timer_start(&timer_mover, timer_mover_cb, 2500, 1000);
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