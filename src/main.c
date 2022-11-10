#include "s21_string.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>
int main() {
    char* dest = malloc(16);
    char* dest2 = malloc(16);
    const char* str = "Teew str";
    const char* str2 = "Teew str";
    printf("%s\n", s21_strcat(dest, str));
    printf("%s\n", s21_strcat(dest2, str2));
    printf("1:%s\n2:%s\n", dest, dest2);
    printf("%i\n", memcmp(dest, str, 1000));
    return 0;
}