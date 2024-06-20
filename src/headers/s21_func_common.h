#ifndef S21_FUNC_COMMON_H_
#define S21_FUNC_COMMON_H_

// #include "s21_func_develop.h"

/*binary operations*/
int getbit(s21_decimal num, int index);
void setbit(s21_decimal *num, int index, int bit);
int getscale(s21_decimal num);  // we use mint because we work with bits
int setscale(s21_decimal *num,
             int scale);  // we use mint because we work with bits
int getsign(s21_decimal num);
void setsign(s21_decimal *num, int sign);
int left_shift(s21_decimal *num, int shift);
void right_shift(s21_decimal *num, int shift);
int big_dec_getbit(s21_decimal num[2], int index);
void big_dec_setbit(s21_decimal num[2], int index, int bit);
int big_dec_getsign(s21_decimal num[2]);
void big_dec_setsign(s21_decimal num[2], int sign);
bool big_dec_is_zero(s21_decimal num_big[2]);
void big_dec_init(s21_decimal num_big[2]);
void big_dec_left_shift(s21_decimal num[2], int shift);
void big_dec_right_shift(s21_decimal num[2], int shift);
void big_dec_twos_compliment(s21_decimal num[2]);
int big_dec_num_len(s21_decimal num_big[2]);

/*other functions*/
s21_decimal dec_def(mint bits1, mint bits2, mint bits3, int scale, int sign);
void set_zero(s21_decimal *num);
bool is_zero(s21_decimal num);
bool is_mantissa_full(s21_decimal num);
void dec_copy(s21_decimal *dest, s21_decimal src);
s21_decimal twos_compliment(s21_decimal num);
int get_last_digit(s21_decimal num);
int normalization_proc(s21_decimal num1, s21_decimal num2,
                       s21_decimal *num1_norm, s21_decimal *num2_norm);
int normalization(s21_decimal num1, s21_decimal num2, s21_decimal *num1_norm,
                  s21_decimal *num2_norm);
int dec_num_len(s21_decimal num);
s21_decimal get_powered_of_ten(int scale);
int get_len_ten_powered(int scale);

void init_num(s21_decimal *num);
int get_bin_float_exp(float src);
int get_bit_float(float num, int indexbit);
void set_zero_header_bit(s21_decimal *num);
void big_dec_copy(s21_decimal dest[2], s21_decimal src[2]);
int big_dec_get_last_digit(s21_decimal num[2]);
void tr_zeroes(unsigned int *str_num, int *scale);
#endif  // S21_FUNC_COMMON_H_