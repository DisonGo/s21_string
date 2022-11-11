#include "../s21_string.h"
#include <stdio.h>
char *s21_strstr (const char *haystack, const char *needle) {
    char* res = NULL;
    char* hay = (char*)haystack;
    for (; *hay != '\0'; hay++) {
        if (*hay == *needle) {
            res = hay;
            char* nd = (char*)needle;
            for (; *nd != '\0'; nd++, hay++) {
                if (*hay != '\0') {
                    res = NULL;
                    break;
                }
                if (*hay != *nd) res = NULL;
            }
        }
    }
    return res;
}