#include <stdlib.h>
#include <string.h>
#include "uv.h"
#include "../snake/snake.h"
#include "../world/world.h"

void graceful_stop_loop_walk_handler(uv_handle_t* handle, void* arg)
{
    uv_close(handle, NULL);
}

void graceful_stop_loop(uv_loop_t* loop) {
    uv_tty_reset_mode();

    uv_walk(loop, graceful_stop_loop_walk_handler, NULL);

    uv_loop_close(loop);
}

void render_world(uv_tty_t* tty_stdout, const world_t* world) {
    const char flusher_operation[] = "\x1b[2J";

    uv_buf_t flusher_buf = { .base = flusher_operation, .len = sizeof(char) * strlen(flusher_operation) };

    uv_write_t flusher_write_req;

    uv_write(&flusher_write_req, (uv_stream_t*) tty_stdout, &flusher_buf, 1, NULL);

    char* world_representation_copy = (char*) malloc(sizeof(char) * world->raw_size);

    memcpy(world_representation_copy, get_world_representation(world), world->raw_size);

    for(int i = 0; i < world->snake->parts_count; i++) {
        snake_part_t* snake_part = &world->snake->parts[i];

        int snake_part_world_coordinates = snake_part->coordinates.y * (world->width + 1) + snake_part->coordinates.x;

        world_representation_copy[snake_part_world_coordinates] = '0';
    }

    for(int i = 0; i < world->apples_count; i++) {
        apple_t apple = world->apples[i];

        int apple_world_coordinates = apple.coordinates.y * (world->width + 1) + apple.coordinates.x;

        world_representation_copy[apple_world_coordinates] = 'Q';
    }

    for(int i = 0; i < world->obstacles_count; i++) {
        obstacle_t obstacle = world->obstacles[i];

        int obstacle_world_coordinates = obstacle.coordinates.y * (world->width + 1) + obstacle.coordinates.x;

        world_representation_copy[obstacle_world_coordinates] = 'X';
    }

    uv_buf_t buf = { .base = strcat(world_representation_copy, "\n"), .len = sizeof(char) * (world->raw_size + 1) };

    uv_write_t write_req;

    uv_write(&write_req, (uv_stream_t*)tty_stdout, &buf, 1, NULL);
}

int assert_snake_on_apple(const world_t* world, snake_t* snake) {
    // Worst case O(n);
    for(int apple_index = 0; apple_index < world->apples_count; apple_index++) {
        if(world->apples[apple_index].coordinates.x == snake->parts[0].coordinates.x && world->apples[apple_index].coordinates.y == snake->parts[0].coordinates.y) {
            return apple_index;
        }
    }

    return 0;
}

int assert_snake_on_obstacle(const world_t* world, snake_t* snake) {
    // Worst case O(n);
    for(int obstacle_index = 0; obstacle_index < world->obstacles_count; obstacle_index++) {
        if(world->obstacles[obstacle_index].coordinates.x == snake->parts[0].coordinates.x && world->obstacles[obstacle_index].coordinates.y == snake->parts[0].coordinates.y) {
            return obstacle_index;
        }
    }

    return 0;
}

int move_snake(world_t* world, snake_t* snake, direction_t direction_operand) {
    int result = 0;

    if(direction_operand == UP)
        result = move_up(snake);

    if(direction_operand == DOWN)
        result = move_down(world->height, snake);

    if(direction_operand == LEFT)
        result = move_left(snake);

    if(direction_operand == RIGHT)
        result = move_right(world->width, snake);

    int apple_index = assert_snake_on_apple(world, snake);
    int obstacle_index = assert_snake_on_obstacle(world, snake);

    if(apple_index > 0) {
        coordinate_t snake_part_coordinates = {.x = snake->parts[snake->parts_count - 1].coordinates.x, .y = snake->parts[snake->parts_count - 1].coordinates.y};
        snake_part_t snake_part = {.coordinates = snake_part_coordinates};

        unbind_apple(world, apple_index);
        bind_snake_part(snake, snake_part);
    }

    if(obstacle_index > 0) {
        return -1;
    }

    return result;
}