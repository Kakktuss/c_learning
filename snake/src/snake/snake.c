#include <stdlib.h>
#include "snake.h"

snake_part_t create_snake_part_entity(coordinate_t coordinates) {
    snake_part_t snake_part;

    snake_part.coordinates = coordinates;

    return snake_part;
}

snake_t create_snake_entity(int parts_count, snake_part_t* parts, direction_t direction){
    snake_t snake;

    snake.parts_count = parts_count;
    snake.parts = malloc(sizeof(snake_part_t) * 100);
    snake.direction = direction;

    for(int i = 0; i < parts_count; ++i) {
        snake.parts[i] = parts[i];
    }

    return snake;
}

void bind_snake_part(snake_t* snake, snake_part_t part) {
    // If the length of the snake is superior than the previously allocated buffer, then alloc with a superior size
    if(snake->parts_count > 100) {
        snake->parts = realloc(snake->parts, sizeof(snake_t) * (snake->parts_count + 100));
    }

    snake->parts_count++;

    snake->parts[snake->parts_count] = part;
}

void move_parts(snake_t* snake) {
    coordinate_t last_snake_part_coordinates = snake->parts[0].coordinates;

    for(size_t i = 1; i < snake->parts_count; i++) {
        coordinate_t buffer_snake_part_coordinates = snake->parts[i].coordinates;

        snake->parts[i].coordinates.y = last_snake_part_coordinates.y;
        snake->parts[i].coordinates.x = last_snake_part_coordinates.x;

        last_snake_part_coordinates = buffer_snake_part_coordinates;
    }
}

int move_down(int world_height, snake_t* snake)
{
    if(snake->parts->coordinates.y >= world_height - 2) {
        return -1;
    }

    move_parts(snake);

    snake->parts[0].coordinates.y += 1;

    snake->direction = DOWN;

    return 0;
}

int move_up(snake_t* snake)
{
    if(snake->parts[0].coordinates.y <= 1) {
        return -1;
    }

    move_parts(snake);

    snake->parts[0].coordinates.y -= 1;

    snake->direction = UP;

    return 0;
}

int move_left(snake_t* snake)
{
    if(snake->parts[0].coordinates.x <= 1) {
        return -1;
    }

    move_parts(snake);

    snake->parts[0].coordinates.x -= 1;

    snake->direction = LEFT;

    return 0;
}

int move_right(int world_width, snake_t* snake)
{
    if(snake->parts[0].coordinates.x >= world_width - 2)
    {
        return -1;
    }

    move_parts(snake);

    snake->parts[0].coordinates.x += 1;

    snake->direction = RIGHT;

    return 0;
}