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
  Field fields[MAX_ARGS] = {0};
  init_fields(fields, MAX_ARGS);
  read_fields(fields, format);
  char output[OUTPUT_BUF_SIZE] = {'\0'};
  va_list args;
  va_start(args, format);
  for (s21_size_t i = 0; i < MAX_ARGS; i++) {
    if (fields[i].specifier == std_f)
      s21_strcat(output, fields[i].value);
    else
      compile_pattern_in_buffer(fields[i], output, args);
  }
  va_end(args);
  s21_strcpy(str, output);
  int res = s21_strlen(str);
  return res;
}
/**
 * @brief Parse pattern string to Field array.
 *
 * @param fields Pointer to Field array.
 * @param pattern Pattern string.
 * @return Pointer to filled Field array.
 * @retval Field*
 */
Field* read_fields(Field* fields, const char* pattern) {
  char* buf = calloc(s21_strlen(pattern) + 1, sizeof(char));
  char* buf_beg = buf;
  if (!buf) return S21_NULL;
  s21_strcpy(buf, pattern);
  char value_buf[VALLUE_BUF_SIZE] = "";
  Read_states cur_state = std_state;
  for (s21_size_t j = 0; *buf != '\0' && j < MAX_ARGS; buf++) {
    Flag_syms flag = flag_map(*buf);
    if (cur_state == std_state)
      if (std_state_func(flag, buf, value_buf, &fields[j], &j, &cur_state))
        continue;
    if (cur_state == flag_state) flag_state_func(flag, &fields[j], &cur_state);
    if (cur_state == width_state)
      width_state_func(&flag, &buf, &fields[j], &cur_state);
    if (cur_state == precise_state)
      precision_state_func(&flag, &buf, &fields[j], &cur_state);
    if (cur_state == length_state)
      if (!length_state_func(flag, &fields[j], &cur_state)) continue;
    if (cur_state == specifier_state)
      specifier_state_func(flag, &fields[j], &j, &cur_state);
  }
  free(buf_beg);
  return fields;
}
/**
 * @brief Initialize function for patter array.
 *
 * @param fields Pattern array.
 * @param size Size of pattern array.
 */
void init_fields(Field* fields, s21_size_t size) {
  if (!fields || !size) return;
  for (s21_size_t i = 0; i < size; i++) {
    fields[i].specifier = 0;
    fields[i].flag = 0;
    fields[i].width = 0;
    fields[i].precision = -1;
    fields[i].length = 0;
    resetBuffer(fields[i].value, VALLUE_BUF_SIZE);
  }
}