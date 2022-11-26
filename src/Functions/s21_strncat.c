#include "../s21_string.h"
/**
 * @brief Concatenation of first N chars to the end of destination string.
 *
 * @param[in] dest Destination.
 * @param[in] src Source.
 * @param[in] n Number of chars.
 * @return Pointer to begining of dest.
 * @retval char*
 */
char* s21_strncat(char* dest, const char* src, s21_size_t n) {
  char* tmp = dest;
  while (*tmp != '\0') tmp++;
  for (s21_size_t i = 0; i < n; i++) *tmp++ = src[i];
  return dest;
}