//
// Created by Kaktus on 13/06/2022.
//

#ifndef SNAKE_ENTITY_H
#define SNAKE_ENTITY_H

#include <stddef.h>

typedef enum direction_s {
    UP,
    DOWN,
    LEFT,
    RIGHT
} direction_t;

typedef struct coordinate_s {
    int x;
    int y;
} coordinate_t;

typedef struct snake_part_s {
    coordinate_t coordinates;
} snake_part_t;

typedef struct snake_s {
    snake_part_t* parts;
    size_t parts_count;
    direction_t direction;
} snake_t;

typedef struct apple_s {
    coordinate_t coordinates;
} apple_t;

typedef struct obstacle_s {
    coordinate_t coordinates;
} obstacle_t;

snake_part_t create_snake_part_entity(coordinate_t coordinates);

snake_t create_snake_entity(int parts_count, snake_part_t* parts, direction_t direction);

void bind_snake_part(snake_t* snake, snake_part_t part);

int move_down(int world_height, snake_t* snake);

int move_up(snake_t* snake);

int move_left(snake_t* snake);

int move_right(int world_width, snake_t* snake);

apple_t create_apple_entity(coordinate_t coordinates);

obstacle_t create_obstacle_entity(coordinate_t coordinates);

#endif //SNAKE_ENTITY_H
