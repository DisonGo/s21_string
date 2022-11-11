#include "../s21_string.h"
static char* base = NULL;
static char* delim_ptr = NULL;
static char* last = NULL;
static void reset_globals() {
    base = NULL;
    last = NULL;
    delim_ptr = NULL;
}
char *s21_strtok (char *str, const char *delim) {
    if (!str && !base) return NULL; 
    if (str) base = str;
    if (delim_ptr) base = delim_ptr + 1;
    if (last || s21_strchr(delim, *base)) while (s21_strchr(delim, *base)) base++;
    if (base) delim_ptr = s21_strpbrk(base, delim);
    if (!delim_ptr) {
        char* res = *base == '\0' ? NULL : base;
        reset_globals();
        return res;
    }
    *delim_ptr = '\0';
    last = base;
    if (last[0] == '\0') {
        reset_globals();
        return NULL;
    }
    return last;

}