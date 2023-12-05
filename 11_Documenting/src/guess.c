/*! @mainpage
 *
 * Usage: guess [OPTIONS...]
 * guess is a program which can guess numbers
 *
 *   -r, --roman                  Use roman numbers for output
 *       --usage                  Give a short usage message
 *   -?, --help                   Give this help list
 */
#include <argp.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdarg.h>
#include <stdbool.h>
#include <libintl.h>

#define _(str) gettext(str)

#define ARRAY_SIZE(x) sizeof(x)/sizeof((x)[0])

/** Table with roman numbers up to 100
 */
const char *roman[] = {
    "N",
    "I",
    "II",
    "III",
    "IV",
    "V",
    "VI",
    "VII",
    "VIII",
    "IX",
    "X",
    "XI",
    "XII",
    "XIII",
    "XIV",
    "XV",
    "XVI",
    "XVII",
    "XVIII",
    "XIX",
    "XX",
    "XXI",
    "XXII",
    "XXIII",
    "XXIV",
    "XXV",
    "XXVI",
    "XXVII",
    "XXVIII",
    "XXIX",
    "XXX",
    "XXXI",
    "XXXII",
    "XXXIII",
    "XXXIV",
    "XXXV",
    "XXXVI",
    "XXXVII",
    "XXXVIII",
    "XXXIX",
    "XL",
    "XLI",
    "XLII",
    "XLIII",
    "XLIV",
    "XLV",
    "XLVI",
    "XLVII",
    "XLVIII",
    "XLIX",
    "L",
    "LI",
    "LII",
    "LIII",
    "LIV",
    "LV",
    "LVI",
    "LVII",
    "LVIII",
    "LIX",
    "LX",
    "LXI",
    "LXII",
    "LXIII",
    "LXIV",
    "LXV",
    "LXVI",
    "LXVII",
    "LXVIII",
    "LXIX",
    "LXX",
    "LXXI",
    "LXXII",
    "LXXIII",
    "LXXIV",
    "LXXV",
    "LXXVI",
    "LXXVII",
    "LXXVIII",
    "LXXIX",
    "LXXX",
    "LXXXI",
    "LXXXII",
    "LXXXIII",
    "LXXXIV",
    "LXXXV",
    "LXXXVI",
    "LXXXVII",
    "LXXXVIII",
    "LXXXIX",
    "XC",
    "XCI",
    "XCII",
    "XCIII",
    "XCIV",
    "XCV",
    "XCVI",
    "XCVII",
    "XCVIII",
    "XCIX",
    "C",
};
static_assert(ARRAY_SIZE(roman) == 1+100);

/** Convert integer to roman string
 *
 * @param dec integer
 * @return const char * pointer to roman string representation
 */
const char *dec2rom(int dec) {
    return dec >= 0 && dec < ARRAY_SIZE(roman) ? roman[dec] : NULL;
}

/** Convert roman string to integer
 *
 * @param const char * pointer to roman string representation
 * @return int integer
 */
int rom2dec(const char *rom) {
    for (int i = 0; i < ARRAY_SIZE(roman); i++) {
        if (strcmp(rom, roman[i]) == 0) {
            return i;
        }
    }

    return -1;
}

typedef struct {
    bool roman;
    bool help;
    bool usage;
} arguments;

/** Parse options
 *
 * @param key current argument key
 * @param arg argument
 * @param state argp state
 * @return error_t error code
 */
static error_t parse_opt (int key, char *arg, struct argp_state *state) {
    arguments *args = state->input;
    switch (key){
        case 'r':
            args->roman = true;
            break;
        case 'u':
            args->usage = true;
            break;
        case '?':
            args->help = true;
            break;
        default:
            return ARGP_ERR_UNKNOWN;
    }
  return 0;
}

/** Print usage
 *
 * @param name binary name
 * @return int 0
 */
int print_usage(const char *name) {
    printf(_("Usage: %s [OPTIONS...]\n"), name);
    return 0;
}

/** Print help
 *
 * @param name binary name
 * @param argp argp parameter structure
 * @param count amount of different options
 * @return int 0
 */
int print_help(const char *name, const struct argp argp, size_t count) {
    print_usage(name);
    printf("%s\n\n", argp.doc);

    const struct argp_option *options = argp.options;

    for (int i = 0; i < count; i++) {
        if (options[i].key != 'u') {
            printf("  -%c, --%-23s%s\n", options[i].key, options[i].name, options[i].doc);
        } else {
            printf("      --%-23s%s\n", options[i].name, options[i].doc);
        }

    }

    printf(_("\nReport bugs to %s\n"), "/dev/null");

    return 0;
}

#ifndef LOCALE_PATH
#define LOCALE_PATH ""
#endif

int main(int argc, char **argv) {
    setlocale(LC_ALL, "");
    bindtextdomain("guess", LOCALE_PATH);
    textdomain("guess");

    const struct argp_option options[] = {
        {"roman", 'r', 0, 0,  _("Use roman numbers for output")},
        {"usage", 'u', 0, 0, _("Give a short usage message")},
        {"help",  '?', 0, 0, _("Give this help list")},

        {0},
    };

    const struct argp argp = {options, parse_opt, 0, _("guess is a program which can guess numbers")};
    arguments args = {};

    argp_parse (&argp, argc, argv, 0, 0, &args);

    if (args.usage) {
        return print_usage(argv[0]);
    } else if (args.help) {
        return print_help(argv[0], argp, ARRAY_SIZE(options) - 1);
    }

    printf(_("Pick a number from the interval [1, %zu] and I'll try to guess it\n"), ARRAY_SIZE(roman) - 1);

    int start, end;


    for (start = 1, end = ARRAY_SIZE(roman); start != end;) {
        int mid = (start + end) / 2;

        if (args.roman) {
            printf(_("Is your number greater than %s (y/n)?\n"), dec2rom(mid));
        } else {
            printf(_("Is your number greater than %d (y/n)?\n"), mid);
        }

        char v[8] = {0};
        scanf("%7s", v);

        if (strcmp(v, _("y")) == 0) {
            start = mid;
        } else if (strcmp(v, _("n")) == 0) {
            end = mid;
        }

    }

    if (args.roman) {
        printf(_("Your number is %s\n"), dec2rom(start));
    } else {
        printf(_("Your number is %d\n"), start);
    }
}
