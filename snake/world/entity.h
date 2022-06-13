//
// Created by Kaktus on 13/06/2022.
//

#ifndef SNAKE_ENTITY_H
#define SNAKE_ENTITY_H

typedef struct coordinate_s {
    int x;
    int y;
} coordinate_t;

typedef struct snake_part_s {
    coordinate_t coordinates;
} snake_part_t;

typedef struct snake_s {
    snake_part_t* parts;
    int length;
} snake_t;

typedef struct apple_s {
    coordinate_t coordinates
} apple_t;

snake_part_t create_snake_part_entity(coordinate_t coordinates);

snake_t create_snake_entity(int parts_count, snake_part_t* parts);

void bind_snake_part(snake_t* snake, snake_part_t* part);

apple_t create_apple_entity(coordinate_t coordinates);

#endif //SNAKE_ENTITY_H
