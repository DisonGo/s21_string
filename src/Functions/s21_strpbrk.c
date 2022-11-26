#include "../s21_string.h"
/**
 * @brief Find first occurrence of any char of str2 in str1.
 *
 * @param[in] str1 Search string.
 * @param[in] str2 Array of search chars.
 * @return Char pointer to found char in str1.
 * @retval char* - char was found
 * @retval S21_NULL - char not found
 */
char *s21_strpbrk(const char *str1, const char *str2) {
  char *res = S21_NULL;
  for (; *str1 != '\0'; ++str1) {
    if (s21_strchr(str2, *str1)) {
      res = (char *)str1;
      break;
    }
  }
  return res;
}