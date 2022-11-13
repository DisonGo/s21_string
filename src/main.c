#include "s21_string.h"
#include "s21_sprintf.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>
int main() {
    // char text[100] = "121ADEssdWDA11212";
    // printf("%s",(char*) s21_trim(text, "1"));
    // float a = -123222.231;
    Field fields[100] = {0};
    read_fields(fields, "sda%-30faaa%i%dAwe");
    for (int i = 0; i < 100; i++) {
        if (fields[i].specifier || fields[i].flag ||
            fields[i].width || fields[i].precise ||
            fields[i].value[0] != '\0') {
            printf("spec:%i\n",fields[i].specifier);
            printf("flag:%i\n",fields[i].flag);
            printf("width:%i\n",fields[i].width);
            printf("precise:%i\n",fields[i].precise);
            printf("length:%i\n",fields[i].length);
            printf("value:%s\n\n",fields[i].value);
        }
    } 
    // printf("sda%-+30f", a);
    return 0;
}