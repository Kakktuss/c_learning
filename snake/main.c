#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void get_world_dimension(char *world, int *height, int *width) {
    bool stop_count_width = false;

    for(int i = 0; world[i] != '\0'; ++i) {
        if(world[i] == '\n') {
            (*height) ++;
            stop_count_width = true;
        }
        if(!stop_count_width) {
            (*width) ++;
        }
    }
}

int main(int argc, char **argv) {
    char *fileName = NULL;
    if (argc > 1) {
        fileName = argv[1];
    } else {
        printf("Enter at least one parameter\n");
        return -1;
    }

    FILE *file = fopen(fileName, "r");
    if(file == NULL) {
        return -1;
    }

    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    fclose(file);

    // Aloc a world based on the size of the file
    char *world = malloc(size);

    file = fopen(fileName, "r"); // Re-open the world file
    size_t read_bytes = fread(world, sizeof(char), size, file);

    // TODO: Change this reopen to a seek at the beginning of the file

    printf("%s\n", world);

    int height = 0;
    int width = 0;
    get_world_dimension(world, &height, &width);

    // TODO: Change this behavior using the libuv event loop & tty in

    bool stop = false;
    while(!stop) {
        int user_input = getchar();
        //Escape
        if(user_input == 27) {
            stop = true;
        }
    }

    free(world);

    fclose(file);

    return 0;
}