#include "../s21_string.h"
int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
    int result = 0;
    for (int i = 0; i < n; i++) {
        if (!result && (str1[i] != str2[i])) result = str1[i] - str2[i];
    }
    return result;
}