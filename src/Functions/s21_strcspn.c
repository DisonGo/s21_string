#include <stdio.h>

#include "../s21_string.h"
/**
 * @brief Calculate length of begging part of str1, which is fully made from
 * chars not included in str2.
 *
 * @param[in] str1 Search string.
 * @param[in] str2 Array of excluded chars.
 * @return Size of found part.
 * @retval s21_size_t
 */
s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t size = 0;
  while (!s21_strchr(str2, *str1) && *str1 != '\0') {
    str1++;
    size++;
  }
  return size;
}