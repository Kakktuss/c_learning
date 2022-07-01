#include <string.h>
#include "../entity/entity.h"
#include "world.h"
#include "uv.h"
#include "../loop/utility.h"
#include "../utility.h"

void world_renderer_timer_handler(uv_tty_t* tty_stdout, world_t* world) {
    render_world(tty_stdout, world);
}

void world_stdin_handler(const uv_buf_t* buf, world_t* world, snake_t* snake, direction_command_buffer_t* direction_command_buffer) {
    direction_t direction;

    if(direction_command_buffer->command_count > 0) {
        return;
    }

    if((!strcmp(buf->base, "Z") || !strcmp(buf->base, "Z\n")) && snake->direction != DOWN)
        direction = UP;
    else if((strcmp(buf->base, "S") == 0 || !strcmp(buf->base, "S\n")) && snake->direction != UP)
        direction = DOWN;
    else if((strcmp(buf->base, "Q") == 0 || !strcmp(buf->base, "Q\n")) && snake->direction != RIGHT)
        direction = LEFT;
    else if((strcmp(buf->base, "D") == 0 || !strcmp(buf->base, "D\n")) && snake->direction != LEFT)
        direction = RIGHT;
    else {
        return;
    }

    direction_command_buffer->commands[0] = direction;
    direction_command_buffer->command_count++;
}