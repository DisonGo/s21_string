#include "../s21_string.h"
/**
 * @brief Find first occurrence of char in str.
 * 
 * @param[in] str Search string.
 * @param[in] c Char to find.
 * @return Pointer to first occurrence of char.
 * @retval char* - char was found
 * @retval S21_NULL - char not found
 */
char *s21_strchr(const char *str, int c) {
  char *res = S21_NULL;
  for (; *str != '\0'; str++) {
    if (*str == c) {
      res = (char *)str;
      break;
    }
  }
  return res;
}