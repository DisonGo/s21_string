#include "../s21_string.h"
char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  s21_size_t src_len = s21_strlen(src);
  n = n < src_len ? n : src_len;
  for (s21_size_t i = 0; i < n; i++) dest[i] = src[i];
  if (n == src_len) dest[n] = '\0';
  return dest;
}