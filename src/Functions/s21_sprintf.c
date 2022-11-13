#include "../s21_sprintf.h"
#include "string.h"
#include <stdio.h>
// static const char* specifiers = "cdifsu%";
// static const char* flags = "-+ ";
// static const char* precisers = ".";
// static const char* lengths = "hl";
// int s21_sprintf (char *str, const char *string,...) {
//     if (!str) return -1;
//     // Field* fields = read_fields(string);
//     int res = -1;
//     return res;
// }
// 
Field* read_fields(Field* fields, const char *pattern) {
    char* buf = calloc(s21_strlen(pattern) + 1, sizeof(char));
    if (!buf) return S21_NULL;
    s21_strcpy(buf, pattern);
    
    // char* beg;
    char value_buf[VALLUE_BUF_SIZE] = "";
    Read_states cur_state = std_state;
    for (s21_size_t i = 0, j = 0; *buf != '\0' && j < 100; buf++, i++) {
        Flag_syms flag = flag_map(*buf);
        if (cur_state & std_state){
            if (!(flag & prcnt_f)) 
                strncat(value_buf, buf, 1);
            if ((flag & prcnt_f || *(buf + 1) == '\0')) {
                if (value_buf[0] != '\0') {
                    fields[j].flag = std_f;
                    s21_strcpy(fields[j].value, value_buf);
                    resetBuffer(value_buf, VALLUE_BUF_SIZE);
                    j++;
                }
                cur_state = flag_state;
                continue;
            }
        }
        if (cur_state & flag_state){
            if (flag == mns_f) fields[j].flag |= mns_f;
            if (flag == pls_f) {
                if (fields[j].flag & blnk_f) fields[j].flag ^= blnk_f;
                fields[j].flag |= pls_f;
            }
            if (flag == blnk_f && !(fields[j].flag & pls_f)) fields[j].flag |= blnk_f;
            if (!(flag >= mns_f && flag <= pls_f)) cur_state = width_state;
        }
        if (cur_state & width_state){
            char* num = calloc(30, sizeof(char));
            char* num_beg = num;
            if (!num) throw_pattern_error(WIDTH_STATE_ERROR " " MEMORY_ERROR);
            if (s21_strchr(DECIMAL_NUMS, *buf)) {
                if (*buf == '0') throw_pattern_error(WIDTH_STATE_ERROR " Bad num");
                while(*buf != '\0' && (flag = flag_map(*buf)) == std_f)
                    *num++ = *buf++;
                int width = atoi(num_beg);
                if (width == 0) throw_pattern_error(WIDTH_STATE_ERROR " width = 0");
                fields[j].width = width;
            }
            cur_state = precise_state;
        }
        if (cur_state & precise_state){
            cur_state = length_state;
        }
        if (cur_state & length_state){
            cur_state = specifier_state;
        }
        if (cur_state & specifier_state){
            if (!(flag >= c_f && flag <= u_f)) throw_pattern_error(SPECIFIER_STATE_ERROR);
            fields[j].specifier = flag;
            j++;
            cur_state = std_state;
        }
    }
    return fields;
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
        case 'c': flag = c_f; break;
        case 'd': flag = d_f; break;
        case 'i': flag = i_f; break;
        case 'f': flag = f_f; break;
        case 's': flag = s_f; break;
        case 'u': flag = u_f; break;
        case '%': flag = prcnt_f; break;
        case '-': flag = mns_f; break;
        case '+': flag = pls_f; break;
        case ' ': flag = blnk_f; break;
        case '.': flag = dot_f; break;
        case 'h': flag = h_f; break;
        case 'l': flag = l_f; break;
        default: flag = std_f; break;
    }
    return flag;
}