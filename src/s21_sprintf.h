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
#ifndef STD_STATE_ERROR
#define STD_STATE_ERROR "STD_STATE_ERROR"
#endif  // STD_STATE_ERROR
#ifndef FLAG_STATE_ERROR
#define FLAG_STATE_ERROR "FLAG_STATE_ERROR"
#endif  // FLAG_STATE_ERROR
#ifndef WIDTH_STATE_ERROR
#define WIDTH_STATE_ERROR "WIDTH_STATE_ERROR"
#endif  // WIDTH_STATE_ERROR
#ifndef PRECISE_STATE_ERROR
#define PRECISE_STATE_ERROR "PRECISE_STATE_ERROR"
#endif  // PRECISE_STATE_ERROR
#ifndef LENGTH_STATE_ERROR
#define LENGTH_STATE_ERROR "LENGTH_STATE_ERROR"
#endif  // LENGTH_STATE_ERROR
#ifndef SPECIFIER_STATE_ERROR
#define SPECIFIER_STATE_ERROR "SPECIFIER_STATE_ERROR"
#endif  // SPECIFIER_STATE_ERROR
#ifndef MEMORY_ERROR
#define MEMORY_ERROR "MEMORY_ERROR"
#endif  // MEMORY_ERROR
#ifndef DECIMAL_NUMS
#define DECIMAL_NUMS "012345689"
#endif  // DECIMAL_NUMS
#ifndef ITOA_SYM_MAP
#define ITOA_SYM_MAP           \
  "zyxwvutsrqponmlkjihgfedcba" \
  "9876543210123456789"        \
  "abcdefghijklmnopqrstuvwxyz"
#endif  // ITOA_SYM_MAP
#ifndef MAX_ARGS
#define MAX_ARGS 100
#endif  // MAX_ARGS
// Pattern symbols bitmask enum
typedef enum {
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

typedef enum {
  std_state = 1 << 0,
  flag_state = 1 << 1,
  width_state = 1 << 2,
  precise_state = 1 << 3,
  length_state = 1 << 4,
  specifier_state = 1 << 5,
} Read_states;

// Pattern (Pattern) struct

typedef struct {
  int specifier;
  int flag;
  int width;
  int precision;
  int length;
  char value[VALLUE_BUF_SIZE];
} Pattern;

// Pattern parser read states functions
Pattern* read_patterns(Pattern* patterns, const char* pattern);
int std_state_func(Flag_syms flag, char* buf, char* value_buf, Pattern* pattern,
                   s21_size_t* fld_j, Read_states* cur_state);
int flag_state_func(Flag_syms flag, Pattern* pattern, Read_states* cur_state);
int width_state_func(Flag_syms* flag, char** buf, Pattern* pattern,
                     Read_states* cur_state);
int precision_state_func(Flag_syms* flag, char** buf, Pattern* pattern,
                         Read_states* cur_state);
int length_state_func(Flag_syms flag, Pattern* pattern, Read_states* cur_state);
int specifier_state_func(Flag_syms flag, Pattern* pattern, s21_size_t* fld_j,
                         Read_states* cur_state);

// (Pattern x argument) linker functions

char* compile_pattern_in_buffer(Pattern pattern, char* buffer, va_list args);
void compile_c_f(char* buffer, int c);
void compile_d_f(char* buffer, long long num, Pattern pattern);
void compile_i_f(char* buffer, long long num, Pattern pattern);
void compile_f_f(char* buffer, double num, Pattern pattern);
int compile_s_f(char* buffer, const char* str, Pattern pattern);
void compile_u_f(char* buffer, long long unsigned num, Pattern pattern);
void compile_ws_f(char* buffer, wchar_t* str, Pattern pattern);

// Pattern value transform functions

void do_flag_transform(char* src, Pattern pattern, int sign, s21_size_t size);
void do_width_transform(char* src, Pattern pattern, s21_size_t size);
void do_precision_transform(char* src, Pattern pattern, s21_size_t size);

// Utility functions

void init_patterns(Pattern* patterns, s21_size_t size);
char* s21_itoa(long long num, char* res, int base);
char* s21_uitoa(long long unsigned num, char* res, int base);
char* s21_dtoa(double x, char* res, int after_point);
int mantissaToStr(unsigned long long x, char* str, int req_c);
void reverse_str(char* str);
void throw_pattern_error(const char* error);
void resetBuffer(char* str, s21_size_t size);
int max(int a, int b);
int min(int a, int b);
int get_first_digit(long long num);
int round_if(int last_num, int i, int d, int last_round);

Flag_syms flag_map(int c);
#endif  // S21_SPRINTF_H_