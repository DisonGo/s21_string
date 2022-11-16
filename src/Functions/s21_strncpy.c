#include "../s21_string.h"
/**
 * @brief Copy first n chars from src to dest.
 * 
 * @param[in] dest Copy destination.
 * @param[in] src Source of copy.
 * @param[in] n Number of bytes to copy.
 * @return Char pointer to begining of destination.
 * @retval char*
 */
char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  s21_size_t src_len = s21_strlen(src);
  n = n < src_len ? n : src_len;
  for (s21_size_t i = 0; i < n; i++) dest[i] = src[i];
  if (n == src_len) dest[n] = '\0';
  return dest;
}