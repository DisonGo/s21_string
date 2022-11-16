#include "../s21_string.h"
/**
 * @brief Copy first n chars from src to dest. More secure then s21_memcpy.
 * 
 * @param[in] dest Copy destination.
 * @param[in] src Source of copy.
 * @param[in] n Number of bytes to copy.
 * @return Void pointer to begining of destination.
 * @retval void*
 */
void* s21_memmove(void* dest, const void* src, s21_size_t n) {
  char* ds = dest;
  char* sr = (char*)src;
  if (ds < sr) {
    while (n--) *ds++ = *sr++;
  } else {
    char* endsr = sr + (n - 1);
    char* endds = ds + (n - 1);
    while (n--) *endds-- = *endsr--;
  }
  return dest;
}