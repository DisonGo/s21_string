#include "../s21_string.h"
#include <stdlib.h>
void *s21_trim (const char *src, const char *trim_chars) {
    s21_size_t src_len = s21_strlen(src);
    char* buf = calloc(src_len + 1, sizeof(char));
    if (!buf) return NULL;
    s21_strcpy(buf, src);
    char* beg = buf, *end = buf + src_len - 1;
    while (s21_strchr(trim_chars, *beg)) {beg++;}
    while (s21_strchr(trim_chars, *end)) {end--;}
    if (*end != '\0') *(end + 1) = '\0';
    char* res = calloc(end - beg + 1, sizeof(char));
    if (!res) return NULL;
    s21_strcpy(res, beg);
    free(buf);
    return res;
}