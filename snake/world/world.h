//
// Created by Kaktus on 12/06/2022.
//

#ifndef SNAKE_WORLD_H
#define SNAKE_WORLD_H

#include <stdio.h>
#include "entity.h"

typedef struct world_s {
    char* world_raw;
    long raw_size;
    int height;
    int width;
    snake_t* snake;
    size_t apples_count;
    apple_t** apples;
    size_t obstacles_count;
    obstacle_t** obstacles;
} world_t;

world_t create_world(FILE* world_file, snake_t* snake, apple_t** apples, size_t apples_count, obstacle_t** obstacles, size_t obstacles_count);

void bind_apple(world_t* world, apple_t* apple);
void bind_obstacle(world_t* world, obstacle_t* obstacle);

char* get_world_representation(world_t* world);
#endif //SNAKE_WORLD_H
