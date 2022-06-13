#include "entity.h"

snake_part_t create_snake_part_entity(coordinate_t coordinates) {
    snake_part_t snake_part;

    snake_part.coordinates = coordinates;

    return snake_part;
}

snake_t create_snake_entity(int parts_count, snake_part_t* parts){
    snake_t snake;

    snake.parts = malloc(sizeof(snake_part_t) * 100);

    return snake;
}

void bind_snake_part(snake_t* snake, snake_part_t* part) {

    snake->length++;

    snake->parts[snake->length] = part;

}

apple_t create_apple_entity(coordinate_t coordinates) {
    apple_t apple;

    apple.coordinates = coordinates;

    return apple;
}
