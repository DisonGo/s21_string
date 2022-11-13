#include "s21_string.h"
#include "s21_sprintf.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>
void printField(Field f, int i) {
    if (!(f.specifier || f.flag || f.width|| f.precise|| f.length|| f.value[0] != '\0')) return;
    printf("%3i|", i);
    printf("%-8i ",f.specifier);
    printf("%-8i ",f.flag);
    printf("%-8i ",f.width);
    printf("%-8i ",f.precise);
    printf("%-8i ",f.length);
    printf("%-s\n",f.value);
}
void printFields(Field* arr, s21_size_t size) {
    if (arr && size) {
        printf("ind|%-8s %-8s %-8s %-8s %-8s %-s\n","spec","flag","width","precise","length","value");
        for (int i = 0; i < 100; i++) printField(arr[i], i);
    }
}
int main() {
    Field fields[100] = {0};
    const char* input_pattern = "sda%-3s3.10sadhlfaaa% i%d-Awe";
    
    read_fields(fields, input_pattern);
    printf("Input string:%s\n", input_pattern);
    printFields(fields, 100);
    return 0;
}