#include <stdlib.h>

#include "../s21_string.h"
/**
 * @brief Create copy of str transformed into lower register.
 *
 * @param[in] str String to copy.
 * @return Void pointer to copied string.
 * @retval void* - copied string
 * @retval S21_NULL - function failed
 */
void *s21_to_lower(const char *str) {
  s21_size_t str_len = s21_strlen(str);
  char *ptr = calloc(str_len + 1, sizeof(char));
  if (!ptr) return S21_NULL;
  for (s21_size_t i = 0; i < str_len; i++)
    ptr[i] = str[i] + ((str[i] >= 'A' && str[i] <= 'Z') ? 32 : 0);
  return ptr;
}