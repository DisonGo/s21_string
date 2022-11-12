#include "../s21_string.h"
void *s21_memmove (void *dest, const void *src, s21_size_t n) {
    char* ds = dest;
    char* sr = (char*)src;
    if (ds < sr) {
        while (n--) *ds++ = *sr++;
    } else {
        char* endsr = sr + (n - 1);
        char* endds = ds + (n - 1);
        while (n--) *endds-- = *endsr--;
    }
    return dest;
}