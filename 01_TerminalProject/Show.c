#include <stdio.h>
#include <assert.h>
#include <curses.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>

#define KEY_ESCAPE 27
#define KEY_SPACE  32

#define TextFormat "%.*s"
#define TextArg(t) (int) (t).size, (t).data
#define TextLine(t, i) ((t).lines.items[(i)])

// Doesn't include newline
#define LineSize(l) ((l).end - (l).begin)
#define LineFormat "%.*s"
#define LineArg(t, i) (int) LineSize(TextLine((t), (i))), &(t).data[TextLine((t), (i)).begin]

#define MIN(a, b) ((a) < (b) ? (a) : (b))

#define LineArgMax(t, i, s) (int) MIN(LineSize(TextLine((t), (i))), s), &(t).data[TextLine((t), (i)).begin]

typedef struct {
    size_t begin;
    size_t end;
} Line;

typedef struct {
    Line *items;
    size_t count;
    size_t capacity;
} Lines;

typedef struct {
    size_t size;
    char *data;
    Lines lines;
} Text;

#define da_append(da, item) do {                                                       \
    if ((da)->count >= (da)->capacity) {                                               \
        (da)->capacity = (da)->capacity == 0 ? 1024 : (da)->capacity*2;           \
        (da)->items = realloc((da)->items, (da)->capacity*sizeof(*(da)->items));       \
        assert((da)->items != NULL);                                                   \
    }                                                                                  \
    (da)->items[(da)->count++] = (item);                                               \
} while (0)



Text open_file(const char *filename) {
    struct stat statbuf;
    stat(filename, &statbuf);
    FILE *in = fopen(filename, "rb");
    Text file = {};
    file.size = statbuf.st_size;
    file.data = malloc(statbuf.st_size);

    size_t read = 0;

    while ((read = fread(file.data, 1, file.size - read, in)) > 0) {}

    fclose(in);

    file.lines.count = 0;

    size_t begin = 0;
    for (size_t i = 0; i < file.size; ++i) {
        if (file.data[i] == '\n') {
            da_append(&file.lines, ((Line) {begin, i}));
            begin = i + 1;
        }
    }
    da_append(&file.lines, ((Line) {begin, file.size}));
    return file;
}

void close_file(Text file) {
    free(file.data);
    free(file.lines.items);
}

#define TEST_SELF_SOURCE

int main(int argc, const char **argv) {
    const char *filename;
    if (argc < 2) {
#ifdef TEST_SELF_SOURCE
        filename = "Show.c";
#else
        printf("Usage: %s <file>\n", argv[0]);
        return 1;
#endif
    } else {
        filename = argv[1];
    }
    Text file = open_file(filename);

    initscr();
    cbreak();
    noecho();

    int width, height;
    getmaxyx(stdscr, height, width);

    bool exit = false;

    int cursor = 0;
    int max_cursor = file.lines.count - height + 2;

    while (!exit) {
        refresh();
        erase();
        mvprintw(0, 0, "File: %s\n", filename);
        hline(ACS_HLINE, width);
        mvaddch(1, 5, ACS_TTEE);
        move(2, 0);
        for (int i = 0; i < height - 2; i++) {
            printw("%5d", cursor + i + 1);
            addch(ACS_VLINE);
            mvprintw(i + 2, 6, LineFormat"\n", LineArgMax(file, cursor + i, width - 6));
        }

        switch(getch()) {
            case KEY_ESCAPE:
                exit = true;
                break;
            case KEY_SPACE:
                cursor++;
                if (cursor >= max_cursor) {
                    cursor = max_cursor;
                }
                break;
        }
    }

    nocbreak();
    echo();
    endwin();
    close_file(file);
    return 0;
}
