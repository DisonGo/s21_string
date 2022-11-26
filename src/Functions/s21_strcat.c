#include "../s21_string.h"
/**
 * @brief Concatenation to the end of destination string.
 *
 * @param[in] dest Destination.
 * @param[in] src Source.
 * @return Pointer to begining of dest.
 * @retval char*
 */
char *s21_strcat(char *dest, const char *src) {
  s21_size_t len_d = s21_strlen(dest);
  int i = 0;
  for (; src[i] != '\0'; i++) dest[len_d + i] = src[i];
  dest[len_d + i] = '\0';
  return dest;
}