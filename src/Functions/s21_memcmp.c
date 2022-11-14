#include "../s21_string.h"
int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
    int result = 0;
    for (s21_size_t i = 0; i < n; i++) {
        if (!result && *(char*)str1 != *(char*)str2)
            result = ((*(char*)str1) - (*(char*)str2));
        str1++;
        str2++;
    }
    return result;
}
