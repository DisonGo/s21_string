#include "../s21_string.h"
char *s21_strcat (char *dest, const char *src) {
    char *tmp = dest;
    while (*dest) { dest++; }
    while ((*dest++ = *src++) != '\0') {}
    return tmp;
}