#include "../s21_string.h"
char* s21_strncat(char* dest, const char* src, s21_size_t n) {
    char* tmp = dest;
    while (*tmp != '\0') tmp++;
    for (s21_size_t i = 0; i < n; i++) *tmp++ = src[i];
    return dest;
}