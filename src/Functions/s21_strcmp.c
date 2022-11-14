#include "../s21_string.h"
int s21_strcmp(const char *str1, const char *str2) {
    int result = 0;
    s21_size_t str_length = strlen(str1) > strlen(str2) ? strlen(str1) : strlen(str2);
    for (int i = 0; i < str_length; i++)
        if (!result && (str1[i] != str2[i])) result = str1[i] - str2[i];
    return result;
}