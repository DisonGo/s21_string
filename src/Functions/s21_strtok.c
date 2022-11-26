#include "../s21_string.h"
static char* base = S21_NULL;
static char* delim_ptr = S21_NULL;
static char* last = S21_NULL;
static void reset_globals() {
  base = S21_NULL;
  last = S21_NULL;
  delim_ptr = S21_NULL;
}
/**
 * @brief Break string str in substrings using array of delimeters delim.
 *
 * @param[in] str String to break.
 * @param[in] delim Array of delimeters.
 * @return Char pointer to substring.
 * @retval char* - substring was found
 * @retval S21_NULL - substring not found
 */
char* s21_strtok(char* str, const char* delim) {
  if (!str && !base) return S21_NULL;
  if (str) base = str;
  if (delim_ptr) base = delim_ptr + 1;
  if (last || s21_strchr(delim, *base))
    while (s21_strchr(delim, *base)) base++;
  if (base) delim_ptr = s21_strpbrk(base, delim);
  if (!delim_ptr) {
    char* res = *base == '\0' ? S21_NULL : base;
    reset_globals();
    return res;
  }
  *delim_ptr = '\0';
  last = base;
  if (last[0] == '\0') {
    reset_globals();
    return S21_NULL;
  }
  return last;
}