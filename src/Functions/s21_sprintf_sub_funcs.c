#include <stdio.h>

#include "../s21_sprintf.h"
/**
 * @brief Pattern parser std_state read fucntion.
 *
 * @param[in] flag Flag of symbol of current char in pattern string.
 * @param[in] buf Pointer on current position in pattern string.
 * @param[out] value_buf Buffer string of value.
 * @param[out] fld Array of parsed patterns.
 * @param[in] fld_j Pointer index of current parsing pattern.
 * @param[out] cur_state Pointer to current read state of parser.
 * @return Bool - if cur_state was switched.
 * @retval int
 */
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
/**
 * @brief Pattern parser flag_state read fucntion.
 *
 * @param[in] flag Flag of symbol of current char in pattern string.
 * @param[in] buf Pointer on current position in pattern string.
 * @param[out] value_buf Buffer string of value.
 * @return Bool - if cur_state was switched.
 * @retval int
 */
int flag_state_func(Flag_syms flag, Field* fld, Read_states* cur_state) {
  if (flag == mns_f) fld->flag |= mns_f;
  if (flag == pls_f) {
    if (fld->flag & blnk_f) fld->flag ^= blnk_f;
    fld->flag |= pls_f;
  }
  if (flag == blnk_f && !(fld->flag & pls_f)) fld->flag |= blnk_f;
  if (!(flag >= mns_f && flag <= blnk_f)) {
    *cur_state = width_state;
    return 1;
  }
  return 0;
}
/**
 * @brief Pattern parser width_state read fucntion.
 *
 * @param[in] flag Pointer to flag of symbol of current char in pattern string.
 * @param[in] buf Pointer to pointer on current position in pattern string.
 * @param[out] fld Array of parsed patterns.
 * @param[out] cur_state Pointer to current read state of parser.
 * @return Bool - if cur_state was switched.
 * @retval int
 */
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
/**
 * @brief Pattern parser precision_state read fucntion.
 *
 * @param[in] flag Pointer to flag of symbol of current char in pattern string.
 * @param[in] buf Pointer to pointer on current position in pattern string.
 * @param[out] fld Array of parsed patterns.
 * @param[out] cur_state Pointer to current read state of parser.
 * @return Bool - if cur_state was switched.
 * @retval int
 */
int precision_state_func(Flag_syms* flag, char** buf, Field* fld,
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
      fld->precision = precision;
    } else {
      fld->precision = 0;
      *flag = flag_map(**buf);
    }
    free(num_beg);
  }
  *cur_state = length_state;
  return 1;
}
/**
 * @brief Pattern parser length_state read fucntion.
 *
 * @param[in] flag Flag of symbol of current char in pattern string.
 * @param[out] fld Array of parsed patterns.
 * @param[out] cur_state Pointer to current read state of parser.
 * @return Bool - if cur_state was switched.
 * @retval int
 */
int length_state_func(Flag_syms flag, Field* fld, Read_states* cur_state) {
  if (flag >= h_f && flag <= l_f) {
    if (flag == l_f) {
      if (fld->length == l_f)
        fld->length = l_l_f;
      else if (fld->length == 0)
        fld->length = l_f;
      else
        throw_pattern_error(LENGTH_STATE_ERROR " length syms mixed");
    }
    if (flag == h_f) {
      if (fld->length != 0)
        throw_pattern_error(LENGTH_STATE_ERROR " length syms mixed");
      fld->length = h_f;
    }
    return 0;
  }
  *cur_state = specifier_state;
  return 1;
}
/**
 * @brief Pattern parser specifier_state read fucntion.
 *
 * @param[in] flag Flag of symbol of current char in pattern string.
 * @param[out] fld Array of parsed patterns.
 * @param[in] fld_j Pointer to index of current parsing pattern.
 * @param[out] cur_state Pointer to current read state of parser.
 * @return Bool - if cur_state was switched.
 * @retval int
 */
int specifier_state_func(Flag_syms flag, Field* fld, s21_size_t* fld_j,
                         Read_states* cur_state) {
  if (!((flag >= c_f && flag <= u_f) || flag == prcnt_f))
    throw_pattern_error(SPECIFIER_STATE_ERROR);
  fld->specifier = flag;
  if (flag == prcnt_f) {
    fld->specifier = std_f;
    s21_strcpy(fld->value, "%");
  }
  (*fld_j)++;
  *cur_state = std_state;
  return 1;
}
/**
 * @brief Compiler of char specifier for Linker.
 *
 * @param[out] buffer Output string.
 * @param[in] c Char to compile.
 * @return Function success.
 * @retval int
 */
int compile_c_f(char* buffer, int c) {
  char str[2] = {c};
  str[1] = '\0';
  s21_strncat(buffer, str, 1);
  return 1;
}
/**
 * @brief Compiler of decimal specifier for Linker.
 *
 * @param buffer Output string.
 * @param num Nummber to compile.
 * @param fld Pattern config.
 * @return Function success.
 * @retval int
 */
int compile_d_f(char* buffer, long long int num, Field fld) {
  return compile_i_f(buffer, num, fld);
}
/**
 * @brief Compiler of integer specifier for Linker.
 *
 * @param buffer Output string.
 * @param num Nummber to compile.
 * @param fld Pattern config.
 * @return Function success.
 * @retval int
 */
int compile_i_f(char* buffer, long long int num, Field fld) {
  if (!num && !fld.precision) return 1;
  int str_size = 30;
  str_size = max(str_size, max(fld.width, fld.precision));
  if (fld.flag & (pls_f | blnk_f)) str_size++;
  char* str = calloc(str_size + 1, 1);
  if (!str) return 0;
  if (fld.precision == -1) fld.precision = 1;
  s21_itoa(num, str, 10);
  do_precision_transform(str, fld, str_size);
  do_flag_transform(str, fld, (num >= 0), str_size);
  do_width_transform(str, fld, str_size);
  s21_strcat(buffer, str);
  free(str);
  return 1;
}
/**
 * @brief Compiler of double specifier for Linker.
 *
 * @param buffer Output string.
 * @param num Number to compile.
 * @param fld Pattern config.
 * @return Function success.
 * @retval int
 */
int compile_f_f(char* buffer, double num, Field fld) {
  if (!num && !fld.precision) return 1;
  int str_size = 1 << 7;
  if (fld.flag & (pls_f | blnk_f)) str_size++;
  char* str = calloc(str_size * 2 + 1, 1);
  if (!str) return 0;
  if (fld.precision == -1) fld.precision = 6;
  s21_dtoa(num, str, fld.precision);
  str_size = max(s21_strlen(str), fld.width);
  str = realloc(str, str_size + 1);
  if (!str) return 0;
  do_flag_transform(str, fld, (num >= 0), str_size);
  do_width_transform(str, fld, str_size);
  s21_strcat(buffer, str);
  free(str);
  return 1;
}
/**
 * @brief Compiler of string specifier for Linker.
 *
 * @param buffer Output string.
 * @param str String to compile.
 * @param fld Pattern config.
 * @return Function success.
 * @retval int
 */
int compile_s_f(char* buffer, const char* str, Field fld) {
  if (!str || !buffer || !fld.specifier) return 0;
  int str_size = s21_strlen(str);
  str_size = str_size > fld.precision ? str_size : fld.precision;
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
/**
 * @brief Compiler of wide string specifier for Linker.
 *
 * @param buffer Output string.
 * @param str Wide string to compile.
 * @param fld Pattern config.
 * @return Function success.
 * @retval int
 */
int compile_ws_f(char* buffer, wchar_t* str, Field fld) {
  if (!str || !buffer || !fld.specifier) return 0;
  char new_str[WCHAR_BUF_SIZE] = {0};
  wcstombs(new_str, str, WCHAR_BUF_SIZE);
  s21_size_t w_len = s21_strlen(new_str);
  do_precision_transform(new_str, fld, w_len);
  do_width_transform(new_str, fld, w_len);
  s21_strcat(buffer, new_str);
  return 1;
}
/**
 * @brief Compiler of unsigned integer specifier for Linker.
 *
 * @param buffer Output string.
 * @param num Number to compile.
 * @param fld Pattern config.
 * @return Function success.
 * @retval int
 */
int compile_u_f(char* buffer, long long unsigned num, Field fld) {
  if (!num && !fld.precision) return 1;
  int str_size = 30;
  str_size = max(str_size, max(fld.width, fld.precision));
  if (fld.flag & (pls_f | blnk_f)) str_size++;
  char* str = calloc(str_size + 1, 1);
  if (!str) return 0;
  if (fld.precision == -1) fld.precision = 1;
  s21_uitoa(num, str, 10);
  do_precision_transform(str, fld, str_size);
  do_flag_transform(str, fld, 1, str_size);
  do_width_transform(str, fld, str_size);
  s21_strcat(buffer, str);
  free(str);
  return 1;
}
/**
 * @brief Flag transform function of compiler value.
 *
 * @param src Output string.
 * @param fld Pattern config.
 * @param sign Sign of value.
 * @param size Allocated size of output string.
 * @return Function success.
 * @retval int
 */
int do_flag_transform(char* src, Field fld, int sign, s21_size_t size) {
  if (!fld.flag || !sign) return 1;
  char* buffer = calloc(size + 1, 1);
  if (!buffer || !size) return 0;
  buffer[0] = fld.flag & pls_f ? '+' : fld.flag & blnk_f ? ' ' : '\0';
  s21_strcat(buffer, src);
  s21_strcpy(src, buffer);
  free(buffer);
  return 1;
}
/**
 * @brief Width transform function of compiler value.
 *
 * @param src Output string.
 * @param fld Pattern config.
 * @param size Allocated size of output string.
 * @return Function success.
 * @retval int
 */
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
    } else {
      s21_strcat(src, buffer);
    }
    free(buffer);
  }
  return 1;
}
/**
 * @brief Precision transform function of compiler value.
 *
 * @param src Output string.
 * @param fld Pattern config.
 * @param size Allocated size of output string.
 * @return Function success.
 * @retval int
 */
int do_precision_transform(char* src, Field fld, s21_size_t size) {
  if (fld.specifier >= d_f && fld.specifier <= i_f) {
    char* ptr_beg_src = src;
    char* buffer = calloc(size, 1);
    if (!buffer) return 0;
    char* ptr_beg_buf = buffer;
    if (*src == '-') {
      buffer[0] = '-';
      buffer++;
      src++;
    }
    int null_count = fld.precision - s21_strlen(src);
    if (null_count <= 0) return 1;
    s21_memset(buffer, '0', null_count);
    s21_strcat(buffer, src);
    s21_strcpy(ptr_beg_src, ptr_beg_buf);
    free(ptr_beg_buf);
  }
  if (fld.specifier == s_f) {
    if (!fld.precision) return 1;
    if ((s21_size_t)fld.precision < size) src[fld.precision] = '\0';
  }
  return 1;
}
/**
 * @brief Pattern Linker.
 *
 * @param field Pattern config.
 * @param buffer Output string.
 * @param args List of s21_sprintf args.
 * @return Output string.
 * @retval char*
 */
char* compile_pattern_in_buffer(Field field, char* buffer, va_list args) {
  int spec = field.specifier;
  if (spec == c_f) compile_c_f(buffer, va_arg(args, int));
  if (spec == f_f) compile_f_f(buffer, va_arg(args, double), field);
  if (spec & (d_f | i_f | u_f | s_f)) {
    int len = field.length;
    if (len == l_l_f) {
      if (spec == d_f) compile_d_f(buffer, va_arg(args, long long int), field);
      if (spec == i_f) compile_i_f(buffer, va_arg(args, long long int), field);
      if (spec == u_f)
        compile_u_f(buffer, va_arg(args, long long unsigned), field);
    }
    if (len == l_f) {
      if (spec == s_f) compile_ws_f(buffer, va_arg(args, wchar_t*), field);
      if (spec == d_f) compile_d_f(buffer, va_arg(args, long int), field);
      if (spec == i_f) compile_i_f(buffer, va_arg(args, long int), field);
      if (spec == u_f) compile_u_f(buffer, va_arg(args, long unsigned), field);
    }
    if (len == h_f || len == 0) {
      if (spec == s_f) {
        if (len == 0)
          compile_s_f(buffer, va_arg(args, char*), field);
        else
          throw_pattern_error("STRING LENGTH ERROR");
      }
      if (spec == d_f) compile_d_f(buffer, va_arg(args, int), field);
      if (spec == i_f) compile_i_f(buffer, va_arg(args, int), field);
      if (spec == u_f) compile_u_f(buffer, va_arg(args, unsigned), field);
    }
  }
  return buffer;
}
/**
 * @brief Double to string converter.
 *
 * @param x Number to convert.
 * @param res Output string.
 * @param after_point Precision.
 * @return Output string.
 * @retval char*
 */
char* s21_dtoa(double x, char* res, int after_point) {
  int main_part = (int)x;
  double mantissa = x - main_part;
  mantissa = mantissa * pow(10, after_point + 1);
  char* c_mantissa = calloc(64 + 1, sizeof(char));
  int round_main_part =
      mantissaToStr((long long unsigned)mantissa, c_mantissa, after_point);
  if (round_main_part || (get_first_digit(mantissa) > 4 && !after_point))
    main_part++;
  s21_itoa(main_part, res, 10);
  if (after_point > 0) res[s21_strlen(res)] = '.';
  s21_strcat(res, c_mantissa);
  free(c_mantissa);
  return res;
}
/**
 * @brief Int to string converter.
 *
 * @param num Number to convert.
 * @param res Output string.
 * @param base Number system to convert to.
 * @return Output string.
 * @retval char*
 */
char* s21_itoa(long long int num, char* res, int base) {
  if (base < 2 || base > 36) {
    *res = '\0';
    return res;
  }
  char *ptr = res, *ptr1 = res, tmp_char;
  long long int tmp_value;
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
/**
 * @brief Unsigned int to string converter.
 *
 * @param num Number to convert.
 * @param res Output string.
 * @param base Number system to convert to.
 * @return Output string.
 * @retval char*
 */
char* s21_uitoa(long long unsigned num, char* res, int base) {
  if (base < 2 || base > 36) {
    *res = '\0';
    return res;
  }
  char *ptr = res, *ptr1 = res, tmp_char;
  long long unsigned tmp_value;
  do {
    tmp_value = num;
    num /= base;
    *ptr++ = ITOA_SYM_MAP[35 + (tmp_value - num * base)];
  } while (num);
  *ptr-- = '\0';
  while (ptr1 < ptr) {
    tmp_char = *ptr;
    *ptr-- = *ptr1;
    *ptr1++ = tmp_char;
  }
  return res;
}
/**
 * @brief Convert floating part of float to string (based on printf rules).
 *
 * @param x Number to convert.
 * @param str Output string.
 * @param req_c Precision.
 * @return If first digit was rounded.
 * @retval int
 */
int mantissaToStr(long long unsigned x, char* str, int req_c) {
  int i = 0;
  int last_num = 0;
  int last_round = 0;
  while (x) {
    int d = (x % 10);
    last_round = round_if(last_num, i, d, last_round);
    str[i] = d + (last_round ? 1 : 0) + '0';
    if (str[i] == ':') str[i] = '0';
    last_num = d;
    x = x / 10;
    i++;
  }
  while (i < req_c) str[i++] = '0';
  i = req_c;
  reverse_str(str);
  str[i] = '\0';
  return last_round;
}
/**
 * @brief IF function to determine if num in mantissa should be rounded.
 * @param last_num Previous number.
 * @param i Index of current number.
 * @param d Current number.
 * @param last_round Was last nummber rounded.
 * @return Bool if num should be rounded.
 * @paragraph
 */
/*
 A: i == 1
 B: Last num == new num == 9
 C: Last number was rounded
 D: If last num == 9 and new num != 9 and it is second itteration
 E: Last num roundble
 Result: (A || D || (B & C)) & E
*/
int round_if(int last_num, int i, int d, int last_round) {
  int A = (i == 1);
  int B = (last_num * d == 81);
  int C = (last_round);
  int D = (last_num == 9 && d != 9 && i - 1 == 1);
  int E = (last_num > 4);
  return ((A || D || (B & C)) & E);
}
/**
 * @brief Recurcive metod to reverse string.
 *
 * @param str String to reverse.
 */
void reverse_str(char* str) {
  static int i, l, temp;
  l = s21_strlen(str);
  if (i < l / 2) {
    temp = str[i];
    str[i] = str[l - i - 1];
    str[l - i - 1] = temp;
    i++;
    reverse_str(str);
  }
}
/**
 * @brief Get the first digit of integer number.
 *
 * @param num Number.
 * @return First digit.
 * @retval int
 */
int get_first_digit(long long int num) {
  int res = num % 10;
  while (num) {
    res = num % 10;
    num /= 10;
  }
  return res;
}
/**
 * @brief Pattern parser error handler.
 *
 * @param error Error string.
 */
void throw_pattern_error(const char* error) {
  fprintf(stderr, "Pattern error: %s", error);
  exit(1);
}
/**
 * @brief Clear string.
 *
 * @param str String to clear.
 * @param size Size of string.
 */
void resetBuffer(char* str, s21_size_t size) {
  for (s21_size_t i = 0; i < size; i++) str[i] = '\0';
}
/**
 * @brief Determine maximum of two integers.
 *
 * @param a First integer.
 * @param b Second integer.
 * @return Maximum.
 * @retval int
 */
int max(int a, int b) { return a > b ? a : b; }
/**
 * @brief Determine minimum of two integers.
 *
 * @param a First integer.
 * @param b Second integer.
 * @return Minimum.
 * @retval int
 */
int min(int a, int b) { return a < b ? a : b; }
/**
 * @brief Flag map of pattern symbols.
 *
 * @param c Char from pattern string.
 * @return Flag of pattern char.
 * @retval Flag_syms
 */
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
/**
 * @brief Count not empty patterns in array.
 *
 * @param fields Array of patterns.
 * @return Count.
 * @retval s21_size_t
 */
s21_size_t count_patterns(Field* fields) {
  s21_size_t count = 0, i;
  for (i = 0; i < MAX_ARGS; i++)
    if (fields[i].specifier != std_f) count++;
  return count;
}