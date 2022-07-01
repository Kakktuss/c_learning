//
// Created by Kaktus on 28/06/2022.
//

#ifndef SNAKE_EVENT_SNAKE_H
#define SNAKE_EVENT_SNAKE_H

#include "uv.h"
#include "../world/world.h"
#include "snake.h"

void snake_mover_timer_handler(uv_loop_t* loop, const uv_tty_t* tty_stdout, direction_command_buffer_t* direction_command_buffer, world_t* world, snake_t* snake);

#endif //SNAKE_EVENT_SNAKE_H
