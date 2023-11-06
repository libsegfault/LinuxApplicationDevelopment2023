#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <strings.h>
#include <ctype.h>
#include <sys/types.h>
#include <rhash.h>

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef USE_READLINE
#include <readline/readline.h>
#include <readline/history.h>
#endif



bool hash_file(const char *path, unsigned alg, uint8_t *digest) {
    if (rhash_file(alg, path, digest) < 0) {
        perror("rhash error");
        return false;
    }
    return true;
}

bool hash_string(const char *str, size_t len, unsigned alg, uint8_t *digest) {
    if (rhash_msg(alg, str, len, digest) < 0) {
        perror("rhash error");
        return false;
    }
    return true;
}

static struct {
    const char *name;
    unsigned value;
} algs[] = {
    {.name = "MD5",  .value = RHASH_MD5 },
    {.name = "SHA1", .value = RHASH_SHA1},
    {.name = "TTH",  .value = RHASH_TTH },
};

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

unsigned get_alg(char *str) {

    for(size_t i = 0; i < ARRAY_SIZE(algs); i++) {
        if (strcasecmp(algs[i].name, str) == 0) {
            return algs[i].value;
        }
    }

    fprintf(stdout, "Unsupported value %s", str);
    return 0;
}

ssize_t my_getline(char **line, size_t *n) {
    const char *const prompt = "> ";
#ifdef USE_READLINE
    (void) n;
    *line = readline(prompt);
    if (*line == NULL)
        return -1;
    return strlen(*line);
#else
    printf(prompt);
    return getline(line, n, stdin);
#endif
}

#define my_continue(line) free(line); (line) = NULL; continue;

int main(void) {
    char *line = NULL;
    size_t len;
    ssize_t nread;

    rhash_library_init();

    while ((nread = my_getline(&line, &len)) != -1) {
        uint8_t digest[64];
        char output[130];
        unsigned hash;
        char *hash_alg;
        char *hash_me;


        if ((hash_alg = strtok(line, " ")) == NULL) {
            fprintf(stderr, "Input format error: <hash type> <\"string\" or filename>\n");
            fprintf(stderr, "                         ^\n");
            my_continue(line);
        }
        hash = get_alg(hash_alg);
        if (hash == 0) {
            my_continue(line);
        }

        if ((hash_me = strtok(NULL, " ")) == NULL) {
            fprintf(stderr, "Input format error: <hash type> <\"string\" or filename>\n");
            fprintf(stderr, "                                            ^\n");
            my_continue(line);
        }

        len = strlen(hash_me);

        if (hash_me[0] == '"') {
            hash_me++;
            len -= 1;
            if (!hash_string(hash_me, len, hash, digest)) {
                my_continue(line);
            }
        } else {
            if (!hash_file(hash_me, hash, digest)) {
                my_continue(line);
            }
        }

        if (islower(hash_alg[0]))
            rhash_print_bytes(output, digest, rhash_get_digest_size(hash), RHPR_BASE64);
        else
            rhash_print_bytes(output, digest, rhash_get_digest_size(hash), RHPR_HEX);

        printf("%s(%*s) = %s\n", rhash_get_name(hash), (int) len, hash_me, output);
        free(line);
        line = NULL;
    }

    free(line);
    return 0;
}
