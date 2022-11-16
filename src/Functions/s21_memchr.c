#include "../s21_string.h"
/**
 * @brief Find first occurrence of char (unsigned) in first n bytes of string.
 * 
 * @param[in] str Search string.
 * @param[in] c Char to search.
 * @param[in] n Number of bytes.
 * @return Void pointer to location in string.
 * @retval void* - char was found
 * @retval S21_NULL - char not found
 */
void* s21_memchr(const void* str, int c, s21_size_t n) {
  const char* ptr = str;
  void* res = S21_NULL;
  for (s21_size_t i = 0; i < n; i++) {
    if (ptr[i] == c) {
      res = (void*)(ptr + i);
      break;
    }
  }
  return res;
}