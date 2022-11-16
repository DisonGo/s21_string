#include "../s21_string.h"
/**
 * @brief Copy first n chars from src to dest.
 * 
 * @param[in] dest Copy destination.
 * @param[in] src Source of copy.
 * @param[in] n Number of bytes to copy.
 * @return Void pointer to begining of destination.
 * @retval void*
 */
void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  char *ptr = dest;
  const char *s = src;
  while (n-- > 0) *ptr++ = *s++;
  return dest;
}