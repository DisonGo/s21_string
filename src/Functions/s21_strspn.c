#include "../s21_string.h"
s21_size_t s21_strspn(const char* str1, const char* str2) {
    int flag = 0;
    const char* str1_def = str1;
    s21_size_t char_length = s21_strlen(str2);
    char* _old_pos = S21_NULL;
    while (!flag) {
        _old_pos = (char*)str1;
        for (s21_size_t i = 0; i < char_length && str1 == _old_pos; i++) {
            if (*str1 == str2[i] && str1 == _old_pos) str1++;
        }
        if (*str1 == '\0' || _old_pos++ == str1) flag = 1;
    }
    return str1 - str1_def;
}