//
// Created by Kaktus on 13/06/2022.
//

#ifndef SNAKE_LOOP_UTILITY_H
#define SNAKE_LOOP_UTILITY_H

#include "../world/world.h"
#include "../snake/snake.h"

void graceful_stop_loop(uv_loop_t* loop);

void render_world(uv_tty_t* tty_stdout, const world_t* world);

int move_snake(const world_t* world, snake_t* snake, direction_t direction_operand);

#endif //SNAKE_LOOP_UTILITY_H
