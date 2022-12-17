#include "../s21_sprintf.h"
/**
 * @brief Sending formated output in str.
 *
 * @param[out] str Output string.
 * @param[in] format Format string.
 * @param[in] ... Arguments for format string.
 * @return Int number of chars inserted in str.
 * @retval int
 */
int s21_sprintf(char* str, const char* format, ...) {
  if (!str) return -1;
  Pattern patterns[MAX_ARGS] = {0};
  init_patterns(patterns, MAX_ARGS);
  read_patterns(patterns, format);
  char output[OUTPUT_BUF_SIZE] = {'\0'};
  va_list args;
  va_start(args, format);
  for (s21_size_t i = 0; i < MAX_ARGS; i++) {
    if (patterns[i].specifier == std_f)
      s21_strcat(output, patterns[i].value);
    else
      compile_pattern_in_buffer(patterns[i], output, args);
  }
  va_end(args);
  s21_strcpy(str, output);
  int res = s21_strlen(str);
  return res;
}
/**
 * @brief Parse pattern string to Pattern array.
 *
 * @param patterns Pointer to Pattern array.
 * @param pattern Pattern string.
 * @return Pointer to filled Pattern array.
 * @retval Pattern*
 */
Pattern* read_patterns(Pattern* patterns, const char* pattern) {
  State_data data = {0};
  data.buffer = calloc(s21_strlen(pattern) + 1, sizeof(char));
  char* buf_beg = data.buffer;
  if (!data.buffer) return S21_NULL;
  s21_strcpy(data.buffer, pattern);
  char value_buf[VALLUE_BUF_SIZE] = "";
  data.value_buffer = value_buf;
  data.cur_state = std_state;
  data.patterns = patterns;
  for (data.j = 0; *data.buffer != '\0' && data.j < MAX_ARGS; data.buffer++) {
    data.flag = flag_map(*data.buffer);
    if (data.cur_state == std_state && std_state_func(&data)) continue;
    if (data.cur_state == flag_state) flag_state_func(&data);
    if (data.cur_state == width_state) width_state_func(&data);
    if (data.cur_state == precise_state) precision_state_func(&data);
    if (data.cur_state == length_state && !length_state_func(&data)) continue;
    if (data.cur_state == specifier_state) specifier_state_func(&data);
  }
  free(buf_beg);
  return data.patterns;
}
/**
 * @brief Initialize function for patter array.
 *
 * @param patterns Pattern array.
 * @param size Size of pattern array.
 */
void init_patterns(Pattern* patterns, s21_size_t size) {
  if (!patterns || !size) return;
  for (s21_size_t i = 0; i < size; i++) {
    patterns[i].specifier = 0;
    patterns[i].flag = 0;
    patterns[i].width = 0;
    patterns[i].precision = -1;
    patterns[i].length = 0;
    resetBuffer(patterns[i].value, VALLUE_BUF_SIZE);
  }
}