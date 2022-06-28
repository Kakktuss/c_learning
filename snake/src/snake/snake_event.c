#include "uv.h"
#include "../world/world.h"
#include "snake.h"
#include "../loop/utility.h"

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