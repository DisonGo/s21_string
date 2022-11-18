#ifndef VALLUE_BUF_SIZE
#define VALLUE_BUF_SIZE 1024
#endif  // VALLUE_BUF_SIZE
#ifndef OUTPUT_BUF_SIZE
#define OUTPUT_BUF_SIZE 1 << 12
#endif  // OUTPUT_BUF_SIZE
#ifndef WCHAR_BUF_SIZE
#define WCHAR_BUF_SIZE 1 << 12
#endif  // OUTPUT_BUF_SIZE
#ifndef S21_SPRINTF_H_
#define S21_SPRINTF_H_
#include <math.h>
#include <stdarg.h>
#include <stdlib.h>

#include "s21_string.h"
#define STD_STATE_ERROR "STD_STATE_ERROR"
#define FLAG_STATE_ERROR "FLAG_STATE_ERROR"
#define WIDTH_STATE_ERROR "WIDTH_STATE_ERROR"
#define PRECISE_STATE_ERROR "PRECISE_STATE_ERROR"
#define LENGTH_STATE_ERROR "LENGTH_STATE_ERROR"
#define SPECIFIER_STATE_ERROR "SPECIFIER_STATE_ERROR"
#define MEMORY_ERROR "MEMORY_ERROR"
#define DECIMAL_NUMS "012345689"
#define ITOA_SYM_MAP           \
  "zyxwvutsrqponmlkjihgfedcba" \
  "9876543210123456789"        \
  "abcdefghijklmnopqrstuvwxyz"
#define MAX_ARGS 100
#define FIELD_INTIALIZER \
  { 0, 0, 0, -1, 0, 0 }
// Pattern symbols bitmask enum
typedef enum _flag_syms {
  std_f = 1 << 0,
  c_f = 1 << 1,
  d_f = 1 << 2,
  i_f = 1 << 3,
  f_f = 1 << 4,
  s_f = 1 << 5,
  u_f = 1 << 6,
  mns_f = 1 << 7,
  pls_f = 1 << 8,
  blnk_f = 1 << 9,
  dot_f = 1 << 10,
  h_f = 1 << 11,
  l_f = 1 << 12,
  l_l_f = 1 << 13,
  prcnt_f = 1 << 14,
} Flag_syms;

// Pattern parser read states bitmask enum

typedef enum _field_read_states {
  std_state = 1 << 0,
  flag_state = 1 << 1,
  width_state = 1 << 2,
  precise_state = 1 << 3,
  length_state = 1 << 4,
  specifier_state = 1 << 5,
} Read_states;

// Pattern (Field) struct

typedef struct _field {
  int specifier;
  int flag;
  int width;
  int precision;
  int length;
  char value[VALLUE_BUF_SIZE];
} Field;

// Pattern parser read states functions

Field* read_fields(Field* fields, const char* pattern);
int std_state_func(Flag_syms flag, char* buf, char* value_buf, Field* fld,
                   s21_size_t* fld_j, Read_states* cur_state);
int flag_state_func(Flag_syms flag, Field* fld, Read_states* cur_state);
int width_state_func(Flag_syms* flag, char** buf, Field* fld,
                     Read_states* cur_state);
int precision_state_func(Flag_syms* flag, char** buf, Field* fld,
                         Read_states* cur_state);
int length_state_func(Flag_syms flag, Field* fld, Read_states* cur_state);
int specifier_state_func(Flag_syms flag, Field* fld, s21_size_t* fld_j,
                         Read_states* cur_state);

// (Pattern x argument) linker functions

char* compile_pattern_in_buffer(Field field, char* buffer, va_list args);
int compile_c_f(char* buffer, int c);
int compile_d_f(char* buffer, long long num, Field fld);
int compile_i_f(char* buffer, long long num, Field fld);
int compile_f_f(char* buffer, double num, Field fld);
int compile_s_f(char* buffer, const char* str, Field fld);
int compile_u_f(char* buffer, long long unsigned num, Field fld);

// Pattern value transform functions

int do_flag_transform(char* src, Field fld, int sign, s21_size_t size);
int do_width_transform(char* src, Field fld, s21_size_t size);
int do_precision_transform(char* src, Field fld, s21_size_t size);

// Utility functions

char* s21_itoa(long long num, char* res, int base);
char* s21_uitoa(long long unsigned num, char* res, int base);
char* s21_dtoa(double x, char* res, int after_point);
int mantissaToStr(unsigned long long x, char* str, int req_c);
void reverse_str(char* str);
void throw_pattern_error(const char* error);
void resetBuffer(char* str, s21_size_t size);
void init_fields(Field* fields, s21_size_t size);
int max(int a, int b);
int min(int a, int b);
int get_first_digit(long long num);
int round_if(int last_num, int i, int d, int last_round);
s21_size_t count_patterns(Field* fields);
Flag_syms flag_map(int c);
#endif  // S21_SPRINTF_H_