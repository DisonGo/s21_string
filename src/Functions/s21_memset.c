#include "../s21_string.h"
/**
 * @brief Copy char (unsigned) to first n bytes of str.
 * 
 * @param[in] str Where to copy.
 * @param[in] c Char to copy.
 * @param[in] n Number of bytes for replacement.
 * @return Void pointer to begining of str.
 * @retval void*
 */
void *s21_memset(void *str, int c, s21_size_t n) {
  char *dest = str;
  for (s21_size_t i = 0; i < n; i++) dest[i] = c;
  return dest;
}