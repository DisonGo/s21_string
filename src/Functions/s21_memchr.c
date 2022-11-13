#include "../s21_string.h"
void *s21_memchr (const void *str, int c, s21_size_t n) {
    const char* ptr = str;
    void* res = S21_NULL;
    for (s21_size_t i = 0; i < n; i++) {
        if (ptr[i] == c) {
            res = (void*) (ptr + i);
            break;
        }
    }
    return res;
}