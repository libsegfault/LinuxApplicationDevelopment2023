#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

typedef enum {
    OK = 0,
    ERR_USAGE,
    ERR_IN_OPEN,
    ERR_OUT_OPEN,
    ERR_OOM,
    ERR_READ,
    ERR_WRITE,
    ERR_IN_CLOSE,
    ERR_OUT_CLOSE,
} State;

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    State state = OK;

    if (argc != 3) {
        printf("Usage: %s in out\n", argv[0]);
        return ERR_USAGE;
    }

    int in, out;

    if ((in = open(argv[1], O_RDONLY)) < 0) {
        perror("Failed to open input file");
        return ERR_IN_OPEN;
    }
    if ((out = open(argv[2], O_WRONLY | O_CREAT, 0777))< 0) {
        perror("Failed to open output file file");
        return ERR_OUT_OPEN;
    }

    uint8_t *buf = malloc(BUFFER_SIZE * sizeof(char));
    if (buf == NULL) {
        printf("Failed to allocate buffer memory\nError:%s\n", strerror(errno));
        return ERR_OOM;
    }

    while (1) {
        size_t sz;
        if ((sz = read(in, buf, BUFFER_SIZE)) < 0) {
            perror("Failed to read from file");
            state = ERR_READ;
            break;
        } else if (sz == 0) {
            break;
        }

        if (write(out, buf, sz) < 0) {
            perror("Failed to write fo file");
            state = ERR_WRITE;
            break;
        }
    }

    if (close(out) < 0) {
        perror("Failed to close output file");
        state = ERR_OUT_CLOSE;
    }
    if (close(in) < 0) {
        perror("Failed to close input file");
        state = ERR_IN_CLOSE;
    }
    if (state == OK) {
        remove(argv[1]);
    } else {
        remove(argv[2]);
    }

    return state;
}
