//
// Created by Kaktus on 28/06/2022.
//

#ifndef SNAKE_EVENT_WORLD_H
#define SNAKE_EVENT_WORLD_H

#include "uv.h"
#include "world.h"

void world_renderer_timer_handler(uv_tty_t* tty_stdout, world_t* world);

void world_stdin_handler(const uv_buf_t* buf, world_t* world, snake_t* snake);

#endif //SNAKE_EVENT_WORLD_H
