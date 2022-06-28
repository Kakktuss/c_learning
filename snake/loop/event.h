//
// Created by Kaktus on 13/06/2022.
//

#ifndef SNAKE_EVENT_H
#define SNAKE_EVENT_H

#include "uv.h"
#include "../world/world.h"

void world_renderer_timer_handler(uv_tty_t* tty_stdout, world_t* world);

void snake_mover_timer_handler(uv_loop_t* loop, const uv_tty_t* tty_stdout, const world_t* world, snake_t* snake);

void world_stdin_handler(const uv_buf_t* buf, world_t* world, snake_t* snake);

#endif //SNAKE_EVENT_H
