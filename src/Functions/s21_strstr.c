#include "../s21_string.h"
/**
 * @brief Find first occurrence of full match of needle in haystack (excluding
 * '\0').
 *
 * @param[in] haystack Search string.
 * @param[in] needle Substring to find.
 * @return Char pointer to found substring.
 * @retval char* - substring was found
 * @retval S21_NULL - substring not found
 */
char* s21_strstr(const char* haystack, const char* needle) {
  char* res = S21_NULL;
  char* hay = (char*)haystack;
  for (; *hay != '\0'; hay++) {
    if (!res) {
      if (*hay == *needle) {
        res = hay;
        char* nd = (char*)needle;
        for (; *nd != '\0'; nd++, hay++) {
          if (*hay == '\0') {
            res = S21_NULL;
            break;
          }
          if (*hay != *nd) res = S21_NULL;
        }
      }
    }
  }
  return res;
}