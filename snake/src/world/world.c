#include <stdlib.h>
#include <stdbool.h>
#include "world.h"
#include "../snake/snake.h"

void init_world_raw(FILE* file, world_t* world) {
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    world->raw_size = size;
    world->world_raw = malloc(sizeof(char) * size);
    world->width = 0;
    world->height = 0;
    world->apples_count = 0;
    world->obstacles_count = 0;

    fread(world->world_raw, sizeof(char), size, file);
}

void init_world_dimensions(world_t* world) {
    bool stop_count_width = false;

    for(int i = 0; world->world_raw[i] != '\0'; ++i) {
        if(world->world_raw[i] == '\n') {
            world->height++;
            stop_count_width = true;
        }
        if(!stop_count_width) {
            world->width++;
        }
    }

    world->height++;
}

void init_world_snake(world_t* world, snake_t* snake) {
    world->snake = snake;
}

world_t create_world(FILE* world_file, snake_t* snake) {
    world_t world;

    init_world_raw(world_file, &world);

    init_world_dimensions(&world);

    init_world_snake(&world, snake);

    world.apples_count = 0;
    world.obstacles_count = 0;

    return world;
}

void bind_apple(world_t* world, apple_t apple) {
    // If there's more apples thhant the maximum allocated in memory, return
    if(world->apples_count > 100)
        return;

    // If the coordinates of the apple are outside of the world, return
    if(apple.coordinates.x < 1 || apple.coordinates.y < 1 || apple.coordinates.x >= world->width || apple.coordinates.y >= world->height)
        return;

    world->apples_count++;

    world->apples[world->apples_count] = apple;
}

void unbind_apple(world_t* world, int apple_index) {
    if(apple_index < 0 || apple_index > world->apples_count - 1)
        return;

    for(size_t current_apple = apple_index; current_apple < world->apples_count - 1; current_apple++) {
        world->apples[current_apple] = world->apples[current_apple + 1];
    }
    world->apples_count--;
}

void bind_obstacle(world_t* world, obstacle_t obstacle) {
    // If there's more obstacles than the maximum allocated in memory, return
    if(world->obstacles_count > 100)
        return;

    // If the coordinates of the obstacle are outside of the world, return
    if((obstacle.coordinates.x <= 0 || obstacle.coordinates.x >= world->width) || (obstacle.coordinates.y <= 0 || obstacle.coordinates.y > world->height))
        return;

    world->obstacles_count++;

    world->obstacles[world->obstacles_count] = obstacle;
}

char* get_world_representation(const world_t* world) {
    return world->world_raw;
}