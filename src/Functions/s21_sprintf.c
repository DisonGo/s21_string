#include "../s21_sprintf.h"
int s21_sprintf(char* str, const char* format, ...) {
  if (!str) return -1;
  Field fields[MAX_ARGS] = {0};
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

Field* read_fields(Field* fields, const char* pattern) {
  char* buf = calloc(s21_strlen(pattern) + 1, sizeof(char));
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
      precise_state_func(&flag, &buf, &fields[j], &cur_state);
    if (cur_state == length_state)
      if (length_state_func(flag, &fields[j], &cur_state)) continue;
    if (cur_state == specifier_state)
      specifier_state_func(flag, &fields[j], &j, &cur_state);
  }
  return fields;
}