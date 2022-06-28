//
// Created by Kaktus on 28/06/2022.
//

#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H

#include "../entity/utility.h"

typedef struct snake_part_s {
    coordinate_t coordinates;
} snake_part_t;

typedef struct snake_s {
    snake_part_t* parts;
    size_t parts_count;
    direction_t direction;
} snake_t;

snake_part_t create_snake_part_entity(coordinate_t coordinates);

snake_t create_snake_entity(int parts_count, snake_part_t* parts, direction_t direction);

void bind_snake_part(snake_t* snake, snake_part_t part);

int move_down(int world_height, snake_t* snake);

int move_up(snake_t* snake);

int move_left(snake_t* snake);

int move_right(int world_width, snake_t* snake);

#endif //SNAKE_SNAKE_H
