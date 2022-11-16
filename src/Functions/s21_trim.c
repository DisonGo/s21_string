#include "../s21_string.h"
#include <stdlib.h>
/**
 * @brief Returns a new string in which all beginning and end occurrences of a set of given characters (trim_chars) from the given string (src) are removed.
 * 
 * @param src Source string.
 * @param trim_chars Array of trimming chars.
 * @return Void pointer to new string.
 * @retval void* - new string
 * @retval S21_NULL - function failed
 */
void* s21_trim(const char* src, const char* trim_chars) {
  s21_size_t src_len = s21_strlen(src);
  char* buf = calloc(src_len + 1, sizeof(char));
  if (!buf) return S21_NULL;
  s21_strcpy(buf, src);
  char *beg = buf, *end = buf + src_len - 1;
  while (s21_strchr(trim_chars, *beg)) {
    beg++;
  }
  while (s21_strchr(trim_chars, *end)) {
    end--;
  }
  if (*end != '\0') *(end + 1) = '\0';
  char* res = calloc(end - beg + 1, sizeof(char));
  if (!res) return S21_NULL;
  s21_strcpy(res, beg);
  free(buf);
  return res;
}