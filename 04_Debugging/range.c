#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    int start, stop, step;
    int curr;
} range;

void argparse(int c, char **v, int *M, int *N, int *S) {

    if (c == 2) {
        sscanf(v[1], "%d", N);
        *S = 1;
        *M = 0;
    } else if (c == 3) {
        sscanf(v[1], "%d", M);
        sscanf(v[2], "%d", N);
        *S = 1;
    } else if (c == 4) {
        sscanf(v[1], "%d", M);
        sscanf(v[2], "%d", N);
        sscanf(v[3], "%d", S);
    } else {
        printf("Usage: %s [M] N [S]\n"
               "Prints numbers in the range [M, N) with step S\n"
               "If S argument is present then M needs to be provided as well\n", v[0]);
        exit(0);
    }
}

void range_init(range *r) {
    r->curr = r->start;
}

bool range_run(range *r) {
    return r->step > 0 ? r->curr < r->stop : r->curr > r->stop;
}

void range_next(range *r) {
    r->curr += r->step;
}

int range_get(range *r) {
    return r->curr;
}


int main(int argc, char *argv[]) {
    range I;
    argparse(argc, argv, &I.start, &I.stop, &I.step);
    for(range_init(&I); range_run(&I); range_next(&I)) {
        printf("%d\n", range_get(&I));
    }
    return 0;
}
