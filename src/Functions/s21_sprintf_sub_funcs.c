#include <stdio.h>

#include "../s21_sprintf.h"
/**
 * @brief Pattern parser std_state read fucntion.
 *
 * @param data Data of pattern parser
 * @return Bool - if cur_state was switched.
 * @retval int
 */
int std_state_func(State_data* data) {
  if (!is_State_data_valid(data)) return 1;
  Flag_syms flag = data->flag;
  char* value_buf = data->value_buffer;
  char* buf = data->buffer;
  Pattern* pattern = &data->patterns[data->j];
  int res = 0;
  if (!(flag & prcnt_f)) s21_strncat(value_buf, buf, 1);
  if ((flag & prcnt_f || *(buf + 1) == '\0')) {
    if (value_buf[0] != '\0') {
      pattern->specifier = std_f;
      s21_strcpy(pattern->value, value_buf);
      resetBuffer(value_buf, VALLUE_BUF_SIZE);
      data->j++;
    }
    data->cur_state = flag_state;
    res = 1;
  }
  return res;
}
/**
 * @brief Pattern parser flag_state read fucntion.
 *
 * @param data Data of pattern parser
 * @return Bool - if cur_state was switched.
 * @retval int
 */
int flag_state_func(State_data* data) {
  if (!is_State_data_valid(data)) return 1;
  Flag_syms flag = data->flag;
  int* f = &data->patterns[data->j].flag;
  int res = 0;
  if (flag == mns_f) *f |= mns_f;
  if (flag == pls_f) {
    if (*f & blnk_f) *f ^= blnk_f;
    *f |= pls_f;
  }
  if (flag == blnk_f && !(*f & pls_f)) *f |= blnk_f;
  if (!(flag >= mns_f && flag <= blnk_f)) {
    data->cur_state = width_state;
    res = 1;
  }
  return res;
}
/**
 * @brief Pattern parser width_state read fucntion.
 *
 * @param data Data of pattern parser
 * @return Bool - if cur_state was switched.
 * @retval int
 */
int width_state_func(State_data* data) {
  if (!is_State_data_valid(data)) return 1;
  Pattern* pattern = &data->patterns[data->j];
  char* buf = data->buffer;
  char* num = calloc(16, sizeof(char));
  char* num_beg = num;
  if (!num) throw_pattern_error(WIDTH_STATE_ERROR " " MEMORY_ERROR);
  if (CHAR_IS_DECIMAL(*buf)) {
    if (*buf == '0') throw_pattern_error(WIDTH_STATE_ERROR " Bad num");
    while (*buf != '\0' && data->flag == std_f) {
      *num++ = *buf;
      buf++;
      data->flag = flag_map(*buf);
    }
    int width = atoi(num_beg);
    if (width == 0) throw_pattern_error(WIDTH_STATE_ERROR " width = 0");
    pattern->width = width;
  }
  free(num_beg);
  data->buffer = buf;
  data->cur_state = precise_state;
  return 1;
}
/**
 * @brief Pattern parser precision_state read fucntion.
 *
 * @param data Data of pattern parser
 * @retval int
 */
int precision_state_func(State_data* data) {
  if (!is_State_data_valid(data)) return 1;
  if (data->flag == dot_f) {
    Pattern* pattern = &data->patterns[data->j];
    char* buf = ++data->buffer;
    data->flag = flag_map(*buf);
    char* num = calloc(16, sizeof(char));
    char* num_beg = num;
    int precision = 0;
    if (!num) throw_pattern_error(PRECISE_STATE_ERROR " " MEMORY_ERROR);
    if (!CHAR_IS_DECIMAL(*buf)) {
      data->flag = flag_map(*buf);
    } else {
      while (*buf != '\0' && data->flag == std_f) {
        *num++ = *buf;
        buf++;
        data->flag = flag_map(*buf);
      }
      if (*num_beg == '0' && *(num_beg + 1) != '\0')
        throw_pattern_error(PRECISE_STATE_ERROR " Bad num");
      precision = atoi(num_beg);
    }
    pattern->precision = precision;
    data->buffer = buf;
    free(num_beg);
  }
  data->cur_state = length_state;
  return 1;
}
/**
 * @brief Pattern parser length_state read fucntion.
 *
 * @param data Data of pattern parser
 * @return Bool - if cur_state was switched.
 * @retval int
 */
int length_state_func(State_data* data) {
  if (!is_State_data_valid(data)) return 1;
  Pattern* pattern = &data->patterns[data->j];
  Flag_syms flag = data->flag;
  int l = pattern->length;
  int err = 0;
  int res = 1;
  if (flag >= h_f && flag <= l_f) {
    if (flag == l_f) {
      if (l == l_f)
        l = l_l_f;
      else if (!l)
        l = l_f;
      else
        err = 1;
    }
    if (flag == h_f) {
      if (l) err = 1;
      l = h_f;
    }
    if (err) throw_pattern_error(LENGTH_STATE_ERROR " length syms mixed");
    res = 0;
  }
  pattern->length = l;
  if (res) data->cur_state = specifier_state;
  return res;
}
/**
 * @brief Pattern parser specifier_state read fucntion.
 *
 * @param data Data of pattern parser
 * @return Bool - if cur_state was switched.
 * @retval int
 */
int specifier_state_func(State_data* data) {
  Pattern* pattern = &data->patterns[data->j];
  Flag_syms flag = data->flag;
  if (!((flag >= c_f && flag <= u_f) || flag == prcnt_f))
    throw_pattern_error(SPECIFIER_STATE_ERROR);
  pattern->specifier = flag;
  if (flag == prcnt_f) {
    pattern->specifier = std_f;
    s21_strcpy(pattern->value, "%");
  }
  data->j++;
  data->cur_state = std_state;
  return 1;
}
/**
 * @brief State_data pointer validator.
 *
 * @param data Validating pointer.
 * @return Bool - if data is valid.
 */
int is_State_data_valid(State_data* data) {
  if (!data) return 0;
  if (!data->buffer || !data->patterns || !data->value_buffer) return 0;
  if (data->j > MAX_ARGS) return 0;
  return 1;
}

/**
 * @brief Compiler of char specifier for Linker.
 *
 * @param[out] buffer Output string.
 * @param[in] c Char to compile.
 */
void compile_c_f(char* buffer, int c) {
  char str[2] = {c};
  str[1] = '\0';
  s21_strncat(buffer, str, 1);
}
/**
 * @brief Compiler of decimal specifier for Linker.
 *
 * @param buffer Output string.
 * @param num Nummber to compile.
 * @param pattern Pattern config.
 */
void compile_d_f(char* buffer, long long num, Pattern pattern) {
  compile_i_f(buffer, num, pattern);
}
/**
 * @brief Compiler of integer specifier for Linker.
 *
 * @param buffer Output string.
 * @param num Nummber to compile.
 * @param pattern Pattern config.
 */
void compile_i_f(char* buffer, long long num, Pattern pattern) {
  if (!num && !pattern.precision) return;
  int str_size = max(128, max(pattern.width, pattern.precision));
  if (pattern.flag & (pls_f | blnk_f)) str_size++;
  char* str = calloc(str_size + 1, 1);
  if (!str) return;
  if (pattern.precision == -1) pattern.precision = 1;
  s21_itoa(num, str, 10);
  do_precision_transform(str, pattern, str_size);
  do_flag_transform(str, pattern, (num >= 0), str_size);
  do_width_transform(str, pattern, str_size);
  s21_strcat(buffer, str);
  free(str);
}
/**
 * @brief Compiler of double specifier for Linker.
 *
 * @param buffer Output string.
 * @param num Number to compile.
 * @param pattern Pattern config.
 */
void compile_f_f(char* buffer, double num, Pattern pattern) {
  if (!num && !pattern.precision) return;
  int str_size = 1 << 7;
  if (pattern.flag & (pls_f | blnk_f)) str_size++;
  char* str = calloc(str_size * 2 + 1, 1);
  if (!str) return;
  if (pattern.precision == -1) pattern.precision = 6;
  s21_dtoa(num, str, pattern.precision);
  str_size = max(s21_strlen(str), pattern.width);
  str = realloc(str, str_size + 1);
  if (!str) return;
  do_flag_transform(str, pattern, (num >= 0), str_size);
  do_width_transform(str, pattern, str_size);
  s21_strcat(buffer, str);
  free(str);
}
/**
 * @brief Compiler of string specifier for Linker.
 *
 * @param buffer Output string.
 * @param str String to compile.
 * @param pattern Pattern config.
 * @return Function success.
 * @retval int
 */
int compile_s_f(char* buffer, const char* str, Pattern pattern) {
  if (!str || !buffer || !pattern.specifier) return 0;
  int str_size = s21_strlen(str);
  str_size = max(str_size, pattern.precision);
  char* new_str = calloc(str_size + 1, 1);
  if (!new_str) return 0;
  s21_strcpy(new_str, str);
  do_precision_transform(new_str, pattern, s21_strlen(str));
  str_size = max(s21_strlen(new_str), pattern.width);
  new_str = realloc(new_str, str_size + 1);
  if (!new_str) return 0;
  do_width_transform(new_str, pattern, str_size);
  s21_strcat(buffer, new_str);
  free(new_str);
  return 1;
}
/**
 * @brief Compiler of wide string specifier for Linker.
 *
 * @param buffer Output string.
 * @param str Wide string to compile.
 * @param pattern Pattern config.
 */
void compile_ws_f(char* buffer, wchar_t* str, Pattern pattern) {
  if (!str || !buffer || !pattern.specifier) return;
  char new_str[WCHAR_BUF_SIZE] = {0};
  wcstombs(new_str, str, WCHAR_BUF_SIZE);
  s21_size_t w_len = s21_strlen(new_str);
  do_precision_transform(new_str, pattern, w_len);
  do_width_transform(new_str, pattern, w_len);
  s21_strcat(buffer, new_str);
}
/**
 * @brief Compiler of unsigned integer specifier for Linker.
 *
 * @param buffer Output string.
 * @param num Number to compile.
 * @param pattern Pattern config.
 */
void compile_u_f(char* buffer, long long unsigned num, Pattern pattern) {
  if (!num && !pattern.precision) return;
  int str_size = 30;
  str_size = max(str_size, max(pattern.width, pattern.precision));
  if (pattern.flag & (pls_f | blnk_f)) str_size++;
  char* str = calloc(str_size + 1, 1);
  if (!str) return;
  if (pattern.precision == -1) pattern.precision = 1;
  s21_uitoa(num, str, 10);
  do_precision_transform(str, pattern, str_size);
  do_flag_transform(str, pattern, 1, str_size);
  do_width_transform(str, pattern, str_size);
  s21_strcat(buffer, str);
  free(str);
}
/**
 * @brief Flag transform function of compiler value.
 *
 * @param src Output string.
 * @param pattern Pattern config.
 * @param sign Sign of value.
 * @param size Allocated size of output string.
 */
void do_flag_transform(char* src, Pattern pattern, int sign, s21_size_t size) {
  if (!pattern.flag || !sign) return;
  char* buffer = calloc(size + 1, 1);
  if (!buffer || !size) return;
  buffer[0] = pattern.flag & pls_f ? '+' : pattern.flag & blnk_f ? ' ' : '\0';
  s21_strcat(buffer, src);
  s21_strcpy(src, buffer);
  free(buffer);
}
/**
 * @brief Width transform function of compiler value.
 *
 * @param src Output string.
 * @param pattern Pattern config.
 * @param size Allocated size of output string.
 */
void do_width_transform(char* src, Pattern pattern, s21_size_t size) {
  if (!pattern.width) return;
  int src_len = s21_strlen(src);
  if (src_len < pattern.width) {
    int space_count = pattern.width - src_len;
    char* buffer = calloc(size, 1);
    if (!buffer) return;
    s21_memset(buffer, ' ', space_count);
    if (!(pattern.flag & mns_f)) {
      s21_strcat(buffer, src);
      s21_strcpy(src, buffer);
    } else {
      s21_strcat(src, buffer);
    }
    free(buffer);
  }
}
/**
 * @brief Precision transform function of compiler value.
 *
 * @param src Output string.
 * @param pattern Pattern config.
 * @param size Allocated size of output string.
 */
void do_precision_transform(char* src, Pattern pattern, s21_size_t size) {
  if (pattern.specifier >= d_f && pattern.specifier <= i_f) {
    char *ptr_beg_src = src, *ptr_beg_buf,
         *buffer = ptr_beg_buf = calloc(size, 1);
    if (!buffer) return;
    if (*src == '-') {
      buffer[0] = '-';
      buffer++;
      src++;
    }
    int null_count = pattern.precision - s21_strlen(src);
    if (null_count <= 0) {
      free(ptr_beg_buf);
      return;
    }
    s21_memset(buffer, '0', null_count);
    s21_strcat(buffer, src);
    s21_strcpy(ptr_beg_src, ptr_beg_buf);
    free(ptr_beg_buf);
  }
  if (pattern.specifier == s_f) {
    if (!pattern.precision) return;
    if ((s21_size_t)pattern.precision < size) src[pattern.precision] = '\0';
  }
}
/**
 * @brief Pattern Linker.
 *
 * @param pattern Pattern config.
 * @param buffer Output string.
 * @param args List of s21_sprintf args.
 * @return Output string.
 * @retval char*
 */
char* compile_pattern_in_buffer(Pattern pattern, char* buffer, va_list args) {
  int s = pattern.specifier;
  if (s == c_f) compile_c_f(buffer, va_arg(args, int));
  if (s == f_f) compile_f_f(buffer, va_arg(args, double), pattern);
  if (s & (d_f | i_f | u_f | s_f)) {
    int l = pattern.length;
    if (l == l_l_f) {
      if (s == d_f) compile_d_f(buffer, va_arg(args, long long), pattern);
      if (s == i_f) compile_i_f(buffer, va_arg(args, long long), pattern);
      if (s == u_f)
        compile_u_f(buffer, va_arg(args, long long unsigned), pattern);
    }
    if (l == l_f) {
      if (s == s_f) compile_ws_f(buffer, va_arg(args, wchar_t*), pattern);
      if (s == d_f) compile_d_f(buffer, va_arg(args, long), pattern);
      if (s == i_f) compile_i_f(buffer, va_arg(args, long), pattern);
      if (s == u_f) compile_u_f(buffer, va_arg(args, long unsigned), pattern);
    }
    if (l == h_f || l == 0) {
      if (s == s_f) {
        if (l) throw_pattern_error("STRING LENGTH ERROR");
        compile_s_f(buffer, va_arg(args, char*), pattern);
      }
      if (s == d_f) compile_d_f(buffer, va_arg(args, int), pattern);
      if (s == i_f) compile_i_f(buffer, va_arg(args, int), pattern);
      if (s == u_f) compile_u_f(buffer, va_arg(args, unsigned), pattern);
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
  mantissa *= pow(10, after_point + 1);
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
char* s21_itoa(long long num, char* res, int base) {
  if (base < 2 || base > 36) {
    *res = '\0';
    return res;
  }
  char *ptr = res, *ptr1 = res, tmp_char;
  long long tmp_value;
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
  int i, l, temp;
  l = s21_strlen(str);
  for (i = 0; i < l / 2; i++) {
    temp = str[i];
    str[i] = str[l - i - 1];
    str[l - i - 1] = temp;
  }
}
/**
 * @brief Get the first digit of integer number.
 *
 * @param num Number.
 * @return First digit.
 * @retval int
 */
int get_first_digit(long long num) {
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
