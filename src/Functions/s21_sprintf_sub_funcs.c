#include "../s21_sprintf.h"
#include <stdio.h>
#include "string.h"
int std_state_func(Flag_syms flag, char* buf, char* value_buf, Field* fld, s21_size_t* fld_j, Read_states* cur_state)  {
  if (!(flag & prcnt_f)) strncat(value_buf, buf, 1);
  if ((flag & prcnt_f || *(buf + 1) == '\0')) {
    if (value_buf[0] != '\0') {
      fld->flag = std_f;
      s21_strcpy(fld->value, value_buf);
      resetBuffer(value_buf, VALLUE_BUF_SIZE);
      (*fld_j)++;
    }
    *cur_state = flag_state;
    return 1;
  }
  return 0;
}
int flag_state_func(Flag_syms flag, Field* fld, Read_states* cur_state) {
  if (flag == mns_f) fld->flag |= mns_f;
  if (flag == pls_f) {
    if (fld->flag & blnk_f) fld->flag ^= blnk_f;
    fld->flag |= pls_f;
  }
  if (flag == blnk_f && !(fld->flag & pls_f)) fld->flag |= blnk_f;
  if (!(flag >= mns_f && flag <= blnk_f)) *cur_state = width_state;
  return 1;
}
int width_state_func(Flag_syms* flag, char* buf, Field* fld, Read_states* cur_state) {
  char* num = calloc(16, sizeof(char));
  char* num_beg = num;
  if (!num) throw_pattern_error(WIDTH_STATE_ERROR " " MEMORY_ERROR);
  if (s21_strchr(DECIMAL_NUMS, *buf)) {
    if (*buf == '0') throw_pattern_error(WIDTH_STATE_ERROR " Bad num");
    while (*buf != '\0' && (*flag = flag_map(*buf)) == std_f)
      *num++ = *buf++;
    int width = atoi(num_beg);
    if (width == 0) throw_pattern_error(WIDTH_STATE_ERROR " width = 0");
    fld->width = width;
  }
  free(num_beg);
  *cur_state = precise_state;
  return 1;
}
int precise_state_func(Flag_syms* flag, char* buf, Field* fld, Read_states* cur_state) {
  if (*flag == dot_f) {
    buf++;
    char* num = calloc(16, sizeof(char));
    char* num_beg = num;
    if (!num) throw_pattern_error(PRECISE_STATE_ERROR " " MEMORY_ERROR);
    if (s21_strchr(DECIMAL_NUMS, *buf)) {
      while (*buf != '\0' && (*flag = flag_map(*buf)) == std_f)
        *num++ = *buf++;
      if (*num_beg == '0' && *(num_beg + 1) != '\0')
        throw_pattern_error(PRECISE_STATE_ERROR " Bad num");
      int precision = atoi(num_beg);
      fld->precise = precision;
    }
    free(num_beg);
  }
  *cur_state = length_state;
  return 1;
}
int length_state_func(Flag_syms flag, Field* fld, Read_states* cur_state) {
  if (flag >= h_f && flag <= l_f) {
    fld->length |= flag;
    return 1;
  }
  *cur_state = specifier_state;
  return 0;
}
int specifier_state_func(Flag_syms flag, Field* fld, s21_size_t* fld_j, Read_states* cur_state) {
  if (!(flag >= c_f && flag <= u_f))
    throw_pattern_error(SPECIFIER_STATE_ERROR);
  fld->specifier = flag;
  (*fld_j)++;
  *cur_state = std_state;
  return 1;
}
void throw_pattern_error(const char* error) {
  fprintf(stderr, "Pattern error: %s", error);
  exit(1);
}
void resetBuffer(char* str, s21_size_t size) {
  for (s21_size_t i = 0; i < size; i++) str[i] = '\0';
}
Flag_syms flag_map(int c) {
  Flag_syms flag = 0;
  switch (c) {
    case 'c':
      flag = c_f;
      break;
    case 'd':
      flag = d_f;
      break;
    case 'i':
      flag = i_f;
      break;
    case 'f':
      flag = f_f;
      break;
    case 's':
      flag = s_f;
      break;
    case 'u':
      flag = u_f;
      break;
    case '%':
      flag = prcnt_f;
      break;
    case '-':
      flag = mns_f;
      break;
    case '+':
      flag = pls_f;
      break;
    case ' ':
      flag = blnk_f;
      break;
    case '.':
      flag = dot_f;
      break;
    case 'h':
      flag = h_f;
      break;
    case 'l':
      flag = l_f;
      break;
    default:
      flag = std_f;
      break;
  }
  return flag;
}