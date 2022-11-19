#include "../s21_string.h"
/**
 * @brief Lexographicly compare first n bytes in strings.
 *
 * @param[in] str1 First string.
 * @param[in] str2 Second string.
 * @param[in] n Number of bytes.
 * @return Lexographical difference in strings.
 * @retval int == 0 - strings are the same
 * @retval int > 0 - str1 is bigger then str2
 * @retval int < 0 - str2 is bigger then str1
 */
int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int result = 0;
    s21_size_t str_length =
      s21_strlen(str1) > s21_strlen(str2) ? s21_strlen(str2) : s21_strlen(str1);
  for (s21_size_t i = 0; i < n; i++) {
    if (!result && (str1[i] != str2[i])) result = str1[i] - str2[i];
  }
  if (!result && s21_strlen(str1) != s21_strlen(str2))
    result = s21_strlen(str1) > s21_strlen(str2) ? str1[str_length] : -1 * str2[str_length];
  return result;
}