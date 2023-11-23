#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define rwall(map, x, y) map[2*((y) - 1) + 1][2*((x) - 1) + 2]
#define bwall(map, x, y) map[2*((y) - 1) + 2][2*((x) - 1) + 1]

int main(int argc, char **argv) {
    const size_t size = 6;
    const size_t map_size = size * 2 + 1;
    const char empty = '.';
    const char full = '#';
    srand(time(NULL));

    char (*map)[map_size] = calloc(sizeof(*map), map_size);

    for (size_t i = 0; i < map_size; i++) {
        for (size_t j = 0; j < map_size; j++) {
            map[i][j] = i & 1 && j & 1 ? empty : full;
        }
    }

    // Binary tree
    // https://habr.com/ru/articles/320140/
    const size_t sx = 1, sy = 1;

    for (size_t y = sy; y <= size; y++) {
        for (size_t x = sy; x <= size; x++) {
            if (y != sy) {
                if (rand() % 2 == 0) {
                    if (x != size) {
                        rwall(map, x, y) = empty;
                    } else {
                        bwall(map, x, y - 1) = empty;
                    }
                } else {
                    bwall(map, x, y - 1) = empty;
                }
            } else if (x != size) {
                rwall(map, x, y) = empty;
            }
        }
    }

    for(size_t i = 0; i < map_size; i++) {
        printf("%.*s\n", (int) map_size, map[i]);
    }

    free(map);
}
