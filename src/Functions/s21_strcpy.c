#include "../s21_string.h"
/**
 * @brief Copy chars from src to dest.
 * 
 * @param[in] dest Copy destination.
 * @param[in] src Source of copy.
 * @return Char pointer to begining of destination.
 * @retval char*
 */
char *s21_strcpy(char *dest, const char *src) {
  char *ptr = dest;
  for (; *src != '\0'; src++, dest++) *dest = *src;
  *dest = '\0';
  return ptr;
}