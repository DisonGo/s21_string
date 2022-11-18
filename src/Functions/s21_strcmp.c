#include "../s21_string.h"
/**
 * @brief Lexographicly compare two strings.
 *
 * @param[in] str1 First string.
 * @param[in] str2 Second string.
 * @return Lexographical difference in strings.
 * @retval int == 0 - strings are the same
 * @retval int > 0 - str1 is bigger then str2
 * @retval int < 0 - str2 is bigger then str1
 */
int s21_strcmp(const char *str1, const char *str2) {
  int result = 0;
  s21_size_t str_length =
      s21_strlen(str1) > s21_strlen(str2) ? s21_strlen(str1) : s21_strlen(str2);
  for (s21_size_t i = 0; i < str_length; i++)
    if (!result && (str1[i] != str2[i])) result = str1[i] - str2[i];
  return result;
}