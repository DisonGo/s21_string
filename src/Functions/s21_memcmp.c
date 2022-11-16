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
int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  int result = 0;
  if (str1 != S21_NULL && str2 != S21_NULL) {
    for (s21_size_t i = 0; i < n; i++) {
      if (!result && *(char *)str1 != *(char *)str2)
        result = ((*(char *)str1) - (*(char *)str2));
      str1++;
      str2++;
    }
  }
  return result;
}
