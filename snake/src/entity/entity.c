#include "entity.h"

apple_t create_apple_entity(coordinate_t coordinates) {
    apple_t apple;

    apple.coordinates = coordinates;

    return apple;
}

obstacle_t create_obstacle_entity(coordinate_t coordinates) {
    obstacle_t obstacle;

    obstacle.coordinates = coordinates;

    return obstacle;
}