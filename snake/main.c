#include <stdio.h>
#include "world/world.h"
#include <uv.h>

FILE* file;
world_t  world;

uv_loop_t *loop;
uv_tty_t tty_stdin;

void init_world(char* file_name) {
    file = fopen(file_name, "r");

    if(file == NULL) {
        return;
    }

    world = create_world(file);
}

void init_loop() {
    loop = uv_default_loop();

    uv_tty_init(loop, &tty_stdin, STDIN_FILENO, 0);
    uv_tty_set_mode(&tty_stdin, UV_TTY_MODE_RAW);

}

void init_loop_handles() {

}

int main(int argc, char **argv) {
    char *fileName = NULL;
    if (argc > 1) {
        fileName = argv[1];
    } else {
        printf("Enter at least one parameter\n");
        return -1;
    }

    init_world(fileName);

    init_loop();

    return 0;
}