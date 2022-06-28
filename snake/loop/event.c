#include <uv.h>
#include <stdlib.h>
#include "event.h"

void graceful_stop_loop_walk_handler(uv_handle_t* handle, void* arg)
{
    uv_close(handle, NULL);
}

void graceful_stop_loop(uv_loop_t* loop) {
    uv_tty_reset_mode();

    uv_walk(loop, graceful_stop_loop_walk_handler, NULL);

    uv_loop_close(loop);
}

void render_world(uv_tty_t* tty_stdout, world_t* world) {
    char* flusher_operation = "\x1b[1;1H";

    uv_buf_t flusher_buf = { .base = flusher_operation, .len = sizeof(char) * strlen(flusher_operation) };

    uv_write_t flusher_write_req;

    uv_write(&flusher_write_req, (uv_stream_t*) tty_stdout, &flusher_buf, 1, NULL);

    char* world_representation_copy = (char*) malloc(sizeof(char) * world->raw_size);

    memcpy(world_representation_copy, get_world_representation(world), world->raw_size);

    for(int i = 0; i < world->snake->parts_count; i++) {
        snake_part_t* snake_part = &world->snake->parts[i];

        int world_coordinates = snake_part->coordinates.y * (world->width + 1) + snake_part->coordinates.x;

        world_representation_copy[world_coordinates] = '0';
    }

    for(int i = 0; i < world->apples_count; i++) {
        apple_t* apple = world->apples[i];


    }

    uv_buf_t buf = { .base = strcat(world_representation_copy, "\n"), .len = sizeof(char) * (world->raw_size + 1) };

    uv_write_t write_req;

    uv_write(&write_req, (uv_stream_t*)tty_stdout, &buf, 1, NULL);
}

void world_renderer_timer_handler(uv_tty_t* tty_stdout, world_t* world) {
    render_world(tty_stdout, world);
}

int move_snake(const world_t* world, snake_t* snake, direction_t direction_operand) {
    if(direction_operand == UP)
        return move_up(snake);

    if(direction_operand == DOWN)
        return move_down(world->height, snake);

    if(direction_operand == LEFT)
        return move_left(snake);

    if(direction_operand == RIGHT)
        return move_right(world->width, snake);
}

void snake_mover_timer_handler(uv_loop_t* loop, const uv_tty_t* tty_stdout, const world_t* world, snake_t* snake) {
    int moved = move_snake(world, snake, snake->direction);

    if(moved == -1) {
        char* loose_message = "Game Over";

        uv_buf_t loose_screen = { .base = loose_message, .len = sizeof(char) * strlen(loose_message) };

        uv_write_t flusher_write_req;

        uv_write(&flusher_write_req, (uv_stream_t*) tty_stdout, &loose_screen, 1, NULL);

        graceful_stop_loop(loop);
    }
}

void world_stdin_handler(const uv_buf_t* buf, world_t* world, snake_t* snake) {
    direction_t direction;

    if(strcmp(buf->base, "Z\n") == 0)
        direction = UP;

    if(strcmp(buf->base, "S\n") == 0)
        direction = DOWN;

    if(strcmp(buf->base, "Q\n") == 0)
        direction = LEFT;

    if(strcmp(buf->base, "D\n") == 0)
        direction = RIGHT;

    move_snake(world, snake, direction);
}