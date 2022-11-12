#include "../s21_string.h"
#include <stdlib.h>
void *s21_insert (const char *src, const char *str, s21_size_t start_index) {
    s21_size_t  src_len = s21_strlen(src),
                str_len = s21_strlen(str),
                sum     = start_index + str_len,
                new_len = (sum > src_len ? sum : src_len);
    if (start_index > src_len) return S21_NULL;
    char* ptr = calloc(new_len + 1, sizeof(char));
    if (!ptr) return S21_NULL;
    s21_strncpy(ptr, src, start_index); 
    s21_strcat(ptr, str);
    s21_strcat(ptr, src + start_index);
    return ptr;
}