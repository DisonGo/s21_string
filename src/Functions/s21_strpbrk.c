#include "../s21_string.h"
char *s21_strpbrk(const char *str1, const char *str2) {
  char *res = S21_NULL;
  for (; *str1 != '\0'; ++str1) {
    if (s21_strchr(str2, *str1)) {
      res = (char *)str1;
      break;
    }
  }
  return res;
}