//
// Created by Kaktus on 28/06/2022.
//

#ifndef SNAKE_ENTITY_UTILITY_H
#define SNAKE_ENTITY_UTILITY_H

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

#endif //SNAKE_ENTITY_UTILITY_H
