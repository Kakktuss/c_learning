#include <string.h>
#include "../entity/entity.h"
#include "world.h"
#include "uv.h"
#include "../loop/utility.h"

void world_renderer_timer_handler(uv_tty_t* tty_stdout, world_t* world) {
    render_world(tty_stdout, world);
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