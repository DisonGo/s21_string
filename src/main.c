#include "s21_string.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>
int main() {
    char text[40] = ",, ,  as , d d , , , ,a   s d sssdddd";
    // printf("%s\n", s21_strstr(text, " "));
    char delims[5] = " d";
    char* token = s21_strtok(text, delims);
    // char* token = strtok(text, delims);
    while (token != NULL) {
        printf("%s\n", token);
        token = s21_strtok(NULL, delims);
        // token = strtok(NULL, delims);
    }
    return 0;
}