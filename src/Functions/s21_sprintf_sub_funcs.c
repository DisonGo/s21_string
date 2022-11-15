#include <stdio.h>
#include "../s21_sprintf.h"
s21_size_t count_patterns(Field* fields) {
  s21_size_t count = 0, i;
  for (i = 0; i < MAX_ARGS; i++)
    if (fields[i].specifier != std_f) count++;
  return count;
}
int std_state_func(Flag_syms flag, char* buf, char* value_buf, Field* fld,
                   s21_size_t* fld_j, Read_states* cur_state) {
  if (!(flag & prcnt_f)) s21_strncat(value_buf, buf, 1);
  if ((flag & prcnt_f || *(buf + 1) == '\0')) {
    if (value_buf[0] != '\0') {
      fld->specifier = std_f;
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
int width_state_func(Flag_syms* flag, char** buf, Field* fld,
                     Read_states* cur_state) {
  char* num = calloc(16, sizeof(char));
  char* num_beg = num;
  if (!num) throw_pattern_error(WIDTH_STATE_ERROR " " MEMORY_ERROR);
  if (s21_strchr(DECIMAL_NUMS, **buf)) {
    if (**buf == '0') throw_pattern_error(WIDTH_STATE_ERROR " Bad num");
    while (**buf != '\0' && (*flag = flag_map(**buf)) == std_f) {
      *num++ = **buf;
      (*buf)++;
    }
    int width = atoi(num_beg);
    if (width == 0) throw_pattern_error(WIDTH_STATE_ERROR " width = 0");
    fld->width = width;
  }
  free(num_beg);
  *cur_state = precise_state;
  return 1;
}
int precise_state_func(Flag_syms* flag, char** buf, Field* fld,
                       Read_states* cur_state) {
  if (*flag == dot_f) {
    (*buf)++;
    char* num = calloc(16, sizeof(char));
    char* num_beg = num;
    if (!num) throw_pattern_error(PRECISE_STATE_ERROR " " MEMORY_ERROR);
    if (s21_strchr(DECIMAL_NUMS, **buf)) {
      while (**buf != '\0' && (*flag = flag_map(**buf)) == std_f) {
        *num++ = **buf;
        (*buf)++;
      }
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
int specifier_state_func(Flag_syms flag, Field* fld, s21_size_t* fld_j,
                         Read_states* cur_state) {
  if (!((flag >= c_f && flag <= u_f) || flag == prcnt_f)) throw_pattern_error(SPECIFIER_STATE_ERROR);
  fld->specifier = flag;
  if (flag == prcnt_f) {
    fld->specifier = std_f;
    s21_strcpy(fld->value, "%");
  }
  (*fld_j)++;
  *cur_state = std_state;
  return 1;
}
int compile_c_f(char* buffer, int c) {
  char str[2] = {c};
  s21_strncat(buffer, str, 1);
  return 1;
}
int compile_d_f(char* buffer, int num, Field fld) {
  int res = compile_i_f(buffer, num, fld);
  return res;
}
int compile_i_f(char* buffer, int num, Field fld) {
  if (!num && !fld.precise) return 1;
  int str_size = 30;
  str_size = max(str_size, max(fld.width, fld.precise));
  if (fld.flag & (pls_f | blnk_f)) str_size++;
  char* str = calloc(str_size + 1, 1);
  if (!str) return 0;
  s21_itoa(num, str, 10);
  do_precision_transform(str, fld, str_size);
  do_flag_transform(str, fld, (num >= 0), str_size);
  do_width_transform(str, fld, str_size);
  s21_strcat(buffer, str);
  free(str);
  return 1;
}
int compile_f_f(char* buffer, double num) {
  char* str = calloc(30, 1);
  if (!str) return 0;
  s21_strcat(buffer, s21_itoa((int)num, str, 10));
  free(str);
  return 1;
}
int compile_s_f(char* buffer, const char* str, Field fld) {
  if (!str || !buffer || !fld.specifier) return 0;
  int str_size = s21_strlen(str);
  char* new_str = calloc(str_size + 1, 1);
  if (!new_str) return 0;
  s21_strcpy(new_str, str);
  do_precision_transform(new_str, fld, s21_strlen(str));
  str_size = max(s21_strlen(new_str), fld.width);
  new_str = realloc(new_str, str_size + 1);
  if (!new_str) return 0;
  do_width_transform(new_str, fld, str_size);
  s21_strcat(buffer, new_str);
  free(new_str);
  return 1;
}
int compile_u_f(char* buffer, unsigned int num) {
  char* str = calloc(30, 1);
  if (!str) return 0;
  s21_strcat(buffer, s21_itoa((int)num, str, 10));
  free(str);
  return 1;
}
int do_flag_transform(char* src, Field fld, int sign, s21_size_t size) {
  if (!fld.flag || !sign) return 1;
  char* buffer = calloc(size, 1);
  if (!buffer || !size) return 0;
  buffer[0] = fld.flag & pls_f ? '+' : fld.flag & blnk_f ? ' ' : '\0';
  s21_strcat(buffer, src);
  s21_strcpy(src, buffer);
  return 1;
}
int do_width_transform(char* src, Field fld, s21_size_t size) {
  if (!fld.width) return 1;
  int src_len = s21_strlen(src);
  if (src_len < fld.width) {
    int space_count = fld.width - src_len;
    char* buffer = calloc(size, 1);
    if (!buffer) return 0;
    s21_memset(buffer, ' ', space_count);
    if (!(fld.flag & mns_f)) {
      s21_strcat(buffer, src);
      s21_strcpy(src, buffer);
    }
    else {
      s21_strcat(src, buffer);
    }
    free(buffer);
  }
  return 1;
  
}
int do_precision_transform(char* src, Field fld, s21_size_t size) {
  if (fld.specifier >= d_f && fld.specifier <= i_f) {
    char* ptr_beg_src = src;
    char* buffer = calloc(size, 1);
    if (!buffer) return 0;
    char* ptr_beg_buf = buffer;
    if (*src == '-') {
      *buffer = *src;
      buffer++;
      src++;
    }
    int null_count = fld.precise - s21_strlen(src);
    if (null_count <= 0) return 1;
    s21_memset(buffer, '0', null_count);
    s21_strcat(buffer, src);
    s21_strcpy(ptr_beg_src, ptr_beg_buf);
  }
  if (fld.specifier == s_f) {
    if (!fld.precise) return 1;
    int str_size = min(size, fld.precise);
    src[str_size] = '\0';
  }
  return 1;
}
char* compile_pattern_in_buffer(Field field, char* buffer, va_list args) {
  if (field.specifier == c_f) compile_c_f(buffer, va_arg(args, int));
  if (field.specifier == d_f) compile_d_f(buffer, va_arg(args, int), field);
  if (field.specifier == i_f) compile_i_f(buffer, va_arg(args, int), field);
  if (field.specifier == f_f) compile_f_f(buffer, va_arg(args, double));
  if (field.specifier == s_f) compile_s_f(buffer, va_arg(args, char*), field);
  if (field.specifier == u_f) compile_u_f(buffer, va_arg(args, unsigned int));
  return buffer;
}
char* s21_dtoa(double x, char* res, int after_point) {
  int main_part = (int)x;
  double mantissa = x - main_part;
  s21_itoa(main_part, res, 10);
  res[s21_strlen(res)] = '.';
  mantissa = mantissa * pow(10, after_point);
  char* c_mantissa = calloc(64 + 1, sizeof(char));
  s21_itoa((int)mantissa, c_mantissa, 10);
  s21_strcat(res, c_mantissa);
  free(c_mantissa);
  return res;
}
char* s21_itoa(int num, char* res, int base) {
  if (base < 2 || base > 36) {
    *res = '\0';
    return res;
  }
  char *ptr = res, *ptr1 = res, tmp_char;
  int tmp_value;
  do {
    tmp_value = num;
    num /= base;
    *ptr++ = ITOA_SYM_MAP[35 + (tmp_value - num * base)];
  } while (num);
  if (tmp_value < 0) *ptr++ = '-';
  *ptr-- = '\0';
  while (ptr1 < ptr) {
    tmp_char = *ptr;
    *ptr-- = *ptr1;
    *ptr1++ = tmp_char;
  }
  return res;
}
void throw_pattern_error(const char* error) {
  fprintf(stderr, "Pattern error: %s", error);
  exit(1);
}
void resetBuffer(char* str, s21_size_t size) {
  for (s21_size_t i = 0; i < size; i++) str[i] = '\0';
}
int max(int a, int b) {return a > b ? a : b;}
int min(int a, int b) {return a < b ? a : b;}
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
