#include <stdlib.h>
#include <stdbool.h>
#include "world.h"

void init_world_size(world_t* world) {
    /* Seek to the start of the file in case it was already used in the past */
    fseek(world->world_file, 0, SEEK_END);
    world->size = ftell(world->world_file);
    fseek(world->world_file, SEEK_END, 0);
}

void init_world_raw(world_t* world) {
    world->world_raw = malloc(sizeof(char) * world->size);

    size_t read_bytes = fread(world->world_raw, sizeof(char), world->size, world->world_file);
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
}

void init_snake(world_t* world, snake_t* snake) {
    world->snake = snake;
}

void init_apples(world_t* world, apple_t** apples, ssize_t apples_count) {
    world->apples = apples;

    world->apples_count = apples_count;
}

world_t create_world(FILE* world_file, snake_t* snake, apple_t** apples, ssize_t apples_count) {
    world_t world;

    world.world_file = world_file;
    world.size = ftell(world_file);
    world.world_raw = malloc(sizeof(char));

    init_world_size(&world);

    init_world_raw(&world);

    init_world_dimensions(&world);

    init_snake(&world, snake);

    if(apples != NULL)
        init_apples(&world, apples, apples_count);

    return world;
}

void bind_apple(world_t* world, apple_t* apple) {
    world->apples_count++;

    world->apples[world->apples_count] = apple;
}