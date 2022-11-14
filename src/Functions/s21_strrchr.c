#include "../s21_string.h"
char *s21_strrchr(const char *str, int c) {
    char* last_pos = S21_NULL;
    for (s21_size_t i = 0; i < s21_strlen(str); i++) {
        if (str[i] == c) last_pos = (char*)(str + i);
    }
    return last_pos;
}