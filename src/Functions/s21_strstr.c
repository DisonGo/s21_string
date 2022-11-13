#include "../s21_string.h"
#include <stdio.h>
char *s21_strstr (const char *haystack, const char *needle) {
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