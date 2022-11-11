#include "../s21_string.h"
char *s21_strcpy (char *dest, const char *src) {
    char* ptr = dest;
    for (; *src != '\0'; src++, dest++) *dest = *src;
    *dest = '\0';
    return ptr;
}