#include "../s21_string.h"
/**
 * @brief Calculate length of string.
 *
 * @param[in] str Input string.
 * @return Size of string.
 * @retval s21_size_t
 */
s21_size_t s21_strlen(const char *str) {
  if (!str) return 0;
  s21_size_t i = 0;
  for (; str[i] != '\0'; i++) {
  }
  return i;
}