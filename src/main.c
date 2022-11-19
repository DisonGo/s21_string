#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_sprintf.h"
#include "s21_string.h"
#include "string.h"
void printField(Field f, int i) {
  if (!(f.specifier || f.flag || f.width || f.precision != -1 || f.length ||
        f.value[0] != '\0'))
    return;
  printf("%3i|", i);
  printf("%-8i ", f.specifier);
  printf("%-8i ", f.flag);
  printf("%-8i ", f.width);
  printf("%-10i ", f.precision);
  printf("%-8i ", f.length);
  printf("'%-s'\n", f.value);
}
void printFields(Field* arr, s21_size_t size) {
  if (arr && size) {
    printf("ind|%-8s %-8s %-8s %-10s %-8s %-s\n", "spec", "flag", "width",
           "precision", "length", "value");
    for (s21_size_t i = 0; i < size; i++) printField(arr[i], i);
  }
}
int main() {
  const char* pattern_3 = "new int is %d new string is %s new inv char is %i";
  int val = 90;
  char c = (char)12; 
  char tmp2[56] = "ngfebapuglwjovtnogpqrtlrrgiqlkjkofmrphxxacszelsvqoevfd";
  char output[VALLUE_BUF_SIZE] = {0};
  s21_sprintf(output, pattern_3, val, tmp2, c);
  sprintf(output, pattern_3, val, tmp2, c);
  printf("%s", output);
  // printf("%i\n", (s21_strcmp("hello", ) == 0)) ;
  return 0;
}