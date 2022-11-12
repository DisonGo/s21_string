#include "../s21_string.h"
#include <stdlib.h>
void *s21_to_lower (const char *str) {
    s21_size_t str_len = s21_strlen(str);
    char* ptr = calloc(str_len + 1, sizeof(char));
    if (!ptr) return S21_NULL;
    for (s21_size_t i = 0; i < str_len; i++)
        ptr[i] = str[i] + ((str[i] >= 'A' && str[i] <= 'Z') ? 32 : 0);
    return ptr;
}