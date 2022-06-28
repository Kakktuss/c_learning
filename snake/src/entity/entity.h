//
// Created by Kaktus on 13/06/2022.
//

#ifndef SNAKE_ENTITY_H
#define SNAKE_ENTITY_H

#include "utility.h"

typedef struct apple_s {
    coordinate_t coordinates;
} apple_t;

typedef struct obstacle_s {
    coordinate_t coordinates;
} obstacle_t;

apple_t create_apple_entity(coordinate_t coordinates);

obstacle_t create_obstacle_entity(coordinate_t coordinates);

#endif //SNAKE_ENTITY_H
