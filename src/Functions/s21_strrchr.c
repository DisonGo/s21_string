#include "../s21_string.h"
/**
 * @brief Find last occurrence of char in str.
 *
 * @param[in] str Search string.
 * @param[in] c Char to find.
 * @return Pointer to last occurrence of char.
 * @retval char* - char was found
 * @retval S21_NULL - char not found
 */
char* s21_strrchr(const char* str, int c) {
  char* last_pos = S21_NULL;
  char* ptr = (char*)str;
  while (*ptr != '\0') {
    if (*ptr == c) last_pos = ptr;
    ptr++;
  }
  return last_pos;
}