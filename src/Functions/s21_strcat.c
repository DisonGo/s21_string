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
  char *tmp = dest;
  while (*dest) {
    dest++;
  }
  while ((*dest++ = *src++) != '\0') {
  }
  return tmp;
}