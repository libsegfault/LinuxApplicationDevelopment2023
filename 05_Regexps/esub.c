#include <regex.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define ErrStr_Format "%.*s"
#define ErrStr_Arg(s) (int)sizeof(s), (s).cstr
typedef struct{
    char cstr[1024];
} ErrorString;

#define MAX_MATCHES 10


bool reg_err(int e, regex_t *r) {
    if (e == 0) return false;
    ErrorString s;
    regerror(e, r, s.cstr, sizeof(s));
    fprintf(stderr, "Error:"ErrStr_Format"\n", ErrStr_Arg(s));
    return true;
}

int main(int argc, char **argv) {
    char *re, *sub, *str;
    if (argc != 4) {
        printf("Usage: %s regexp substitution string\n", argv[0]);
        return 1;
    }
    re  = argv[1];
    sub = argv[2];
    str = argv[3];

    regex_t reg;
    regmatch_t matches[MAX_MATCHES];

    if (reg_err(regcomp(&reg, re, REG_EXTENDED), &reg)) {
        return 1;
    }

    if (reg_err(regexec(&reg, str, MAX_MATCHES, matches, 0), &reg)) {
        return 1;
    }

    size_t n;

    for (n = 1; n < MAX_MATCHES && matches[n].rm_so >= 0; n++) {}
    n--;

    size_t str_len = strlen(str);

    size_t len = str_len - (matches[0].rm_eo - matches[0].rm_so);
    size_t sub_len = strlen(sub);

    for (size_t i = 0; i < sub_len; i++) {
        if (sub[i] == '\\' && (i + 1) < sub_len) {
            if (isdigit(sub[i + 1])) {
                size_t m = sub[i + 1] - '0';
                if (m > n) {
                    fprintf(stderr, "Match %zu does not exist\n", m);
                    return 1;
                }
                len += matches[m].rm_eo - matches[m].rm_so;
                i++;
            } else if (sub[i + 1] == '\\') {
                len++;
                i++;
            }
        } else {
            len++;
        }
    }

    char *ans = calloc(len + 1, sizeof(char));

    size_t idx = matches[0].rm_so;
    memcpy(ans, str, idx);

    for (size_t i = 0; i < sub_len; i++) {
        if (sub[i] == '\\' && (i + 1) < sub_len) {
            if (isdigit(sub[i + 1])) {
                size_t n = sub[i + 1] - '0';
                size_t m_len = matches[n].rm_eo - matches[n].rm_so;
                memcpy(&ans[idx], str + matches[n].rm_so, m_len);
                idx += m_len;
                i++;
            }else if (sub[i + 1] == '\\') {
                ans[idx++] = '\\';
                i++;
            }
        } else {
            ans[idx++] = sub[i];
        }
    }

    memcpy(&ans[len + matches[0].rm_eo - str_len], &str[matches[0].rm_eo], str_len - matches[0].rm_eo);

    printf("%s\n", ans);
    regfree(&reg);

    return 0;
}
