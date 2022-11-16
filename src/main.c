#include <stdio.h>
#include <stdlib.h>

#include "s21_sprintf.h"
#include "s21_string.h"
#include "string.h"
void printField(Field f, int i) {
  if (!(f.specifier || f.flag || f.width || f.precision || f.length ||
        f.value[0] != '\0'))
    return;
  printf("%3i|", i);
  printf("%-8i ", f.specifier);
  printf("%-8i ", f.flag);
  printf("%-8i ", f.width);
  printf("%-8i ", f.precision);
  printf("%-8i ", f.length);
  printf("'%-s'\n", f.value);
}
void printFields(Field* arr, s21_size_t size) {
  if (arr && size) {
    printf("ind|%-8s %-8s %-8s %-8s %-8s %-s\n", "spec", "flag", "width",
           "precision", "length", "value");
    for (s21_size_t i = 0; i < size; i++) printField(arr[i], i);
  }
}
int main() {
  Field fields[100] = {0};
  const char* input_pattern = "%-21.10f";
  // const char* str2 = "123456";
  double test = 123.021112;
  char* str = calloc(100, 1);
  // int a = -123;
  s21_sprintf(str, input_pattern, test);
  read_fields(fields, input_pattern);
  printFields(fields, 100);
  printf("Input string:%s\n", input_pattern);
  printf("Output:'%s'\n", str);
  printf("Printf:'");
  printf(input_pattern, test);
  printf("'\n");
  free(str);
  return 0;
}