#ifndef VALLUE_BUF_SIZE
#define VALLUE_BUF_SIZE 1024
#endif  // VALLUE_BUF_SIZE

#ifndef S21_SPRINTF_H_
#define S21_SPRINTF_H_
#include "s21_string.h"
#include <stdlib.h>
#define STD_STATE_ERROR "STD_STATE_ERROR"
#define FLAG_STATE_ERROR "FLAG_STATE_ERROR"
#define WIDTH_STATE_ERROR "WIDTH_STATE_ERROR"
#define PRECISE_STATE_ERROR "PRECISE_STATE_ERROR"
#define LENGTH_STATE_ERROR "LENGTH_STATE_ERROR"
#define SPECIFIER_STATE_ERROR "SPECIFIER_STATE_ERROR"
#define MEMORY_ERROR "MEMORY_ERROR"
#define DECIMAL_NUMS "012345689"
typedef enum _flag_syms {
    std_f   = 1 << 0,
    c_f     = 1 << 1,
    d_f     = 1 << 2,
    i_f     = 1 << 3,
    f_f     = 1 << 4,
    s_f     = 1 << 5,
    u_f     = 1 << 6,
    mns_f   = 1 << 7,
    pls_f   = 1 << 8,
    blnk_f  = 1 << 9,
    dot_f   = 1 << 10,
    h_f     = 1 << 11,
    l_f     = 1 << 12,
    prcnt_f = 1 << 13,
}Flag_syms;
typedef enum _field_read_states {
    std_state        = 1 << 0, 
    flag_state       = 1 << 1, 
    width_state      = 1 << 2, 
    precise_state    = 1 << 3, 
    length_state     = 1 << 4, 
    specifier_state  = 1 << 5, 
}Read_states;
typedef struct _field {
    int specifier;
    int flag;
    int width;
    int precise;
    int length;
    char value[VALLUE_BUF_SIZE];
}Field;
Field* read_fields(Field* fields, const char *pattern);
Flag_syms flag_map(int c);
void throw_pattern_error(const char* error);
void resetBuffer(char* str, s21_size_t size);
#endif  // S21_SPRINTF_H_