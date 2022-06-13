//
// Created by Kaktus on 12/06/2022.
//

#ifndef SNAKE_WORLD_H
#define SNAKE_WORLD_H

#include <stdio.h>
#include "entity.h"

typedef struct s_world {
    FILE* world_file;
    char* world_raw;
    int size;
    int height;
    int width;
    snake_t* snake;
    ssize_t apples_count;
    apple_t** apples;
} world_t;

world_t create_world(FILE* world_file, snake_t* snake, apple_t** apples, ssize_t apples_count);

#endif //SNAKE_WORLD_H
