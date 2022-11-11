#include "../s21_string.h"
char *s21_strchr (const char *str, int c) {
    char* res = NULL;
    for (; *str != '\0'; str++){
        if (*str == c) {
            res = (char*)str;
            break;
        }
    }
    return res;
}