#include "../s21_string.h"
char* s21_strrchr(const char* str, int c) {
  char* last_pos = S21_NULL;
  char* ptr = (char*)str;
  while (*ptr != '\0') {
    if (*ptr == c) last_pos = ptr;
    ptr++;
  }
  return last_pos;
}