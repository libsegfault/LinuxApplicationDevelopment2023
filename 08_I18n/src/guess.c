#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdarg.h>
#include <stdbool.h>
#include <libintl.h>

#define _(str) gettext(str)

int main(int argc, char **argv) {
    setlocale(LC_ALL, "");
    bindtextdomain("guess", LOCALE_PATH);
    textdomain("guess");

    puts(_("Pick a number from the interval [1, 100] and I'll try to guess it"));

    int start, end;


    for (start = 1, end = 100; start != end;) {
        int mid = (start + end) / 2;

        printf(_("Is your number greater than %d (y/n)?\n"), mid);

        char v[8] = {0};
        scanf("%7s", v);

        if (strcmp(v, _("y")) == 0) {
            start = mid + 1;
        } else if (strcmp(v, _("n")) == 0) {
            end = mid;
        }

    }

    printf(_("Your number is %d\n"), start);
}
