#include "../s21_string.h"
/**
 * @brief Calculate length of begging part of str1, which is fully made from
 * chars included in str2.
 *
 * @param[in] str1 Search string.
 * @param[in] str2 Array of included chars.
 * @return Size of found part.
 * @retval s21_size_t
 */
s21_size_t s21_strspn(const char* str1, const char* str2) {
  int do_loop = 1;
  const char* str1_def = str1;
  s21_size_t char_length = s21_strlen(str2);
  char* _old_pos = S21_NULL;
  while (do_loop) {
    _old_pos = (char*)str1;
    for (s21_size_t i = 0; i < char_length && str1 == _old_pos; i++) {
      if (*str1 == str2[i] && str1 == _old_pos) str1++;
    }
    if (*str1 == '\0' || _old_pos++ == str1) do_loop = 0;
  }
  return str1 - str1_def;
}