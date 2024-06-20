#include "../s21_decimal.h"

// typedef enum {
//   err_code_arithmetic_no_err = 0,
//   err_code_arithmetic_too_large_or_inf = 1,
//   err_code_arithmetic_too_small_or_negative_inf = 2,
//   err_code_arithmetic_div_by_zero = 3
// } err_code_arithmetic;

// -79,228,162,514,264,337,593,543,950,335 до
// +79,228,162,514,264,337,593,543,950,335
// 7,8*10^28 < dec_num < 8*10^28

void sum_two_bit_any_index(s21_decimal num1, s21_decimal num2, s21_decimal *res,
                           int index1, int index2, int index_res,
                           int *next_digit) {
  int bit1 = getbit(num1, index1);
  int bit2 = getbit(num2, index2);
  int bits_sum = bit1 + bit2 + *next_digit;
  *next_digit = (bit1 & bit2) | ((bit1 | bit2) & *next_digit);
  setbit(res, index_res, bits_sum & 1);
}

void sum_two_bit(s21_decimal num1, s21_decimal num2, s21_decimal *res,
                 int index, int *next_digit) {
  sum_two_bit_any_index(num1, num2, res, index, index, index, next_digit);
}

int add_mantissa(s21_decimal num1, s21_decimal num2, s21_decimal *res) {
  int next_digit = 0;
  for (int i = 0; i < SIZE_OF_MANTISSA; i++) {
    sum_two_bit(num1, num2, res, i, &next_digit);
  }
  sum_two_bit(num1, num2, res, index_sign_bit,
              &next_digit);  // <- for "compliment" sum
  return err_code_arithmetic_no_err;
}

int add_mantissa_with_twos_compliment(s21_decimal num1, s21_decimal num2,
                                      s21_decimal *res) {
  s21_decimal num1_twos_comp = twos_compliment(num1);
  s21_decimal num2_twos_comp = twos_compliment(num2);

  add_mantissa(num1_twos_comp, num2_twos_comp, res);

  int sign1 = getsign(num1_twos_comp);
  int sign2 = getsign(num2_twos_comp);
  int sign3 = getsign(*res);

  if (sign1 == sign2 && sign1 == 0 && sign3 == 1) {
    return err_code_arithmetic_too_large_or_inf;
  } else if (sign1 == sign2 && sign1 == 1 && sign3 == 0) {
    return err_code_arithmetic_too_small_or_negative_inf;
  }

  if (getsign(*res)) *res = twos_compliment(*res);
  return err_code_arithmetic_no_err;
}

int base_add(s21_decimal num1, s21_decimal num2, s21_decimal *res) {
  return add_mantissa_with_twos_compliment(num1, num2, res);
}

int s21_add(s21_decimal num1, s21_decimal num2, s21_decimal *res) {
  if (res == NULL) {
    return err_code_NULL_pointer;
  }
  init_num(res);
  normalization(num1, num2, &num1, &num2);
  setscale(res, getscale(num1));
  return base_add(num1, num2, res);
}

/* big decimal */

void add_mantissa_big(s21_decimal num1[2], s21_decimal num2[2],
                      s21_decimal res[2]) {
  int next_digit = 0;
  for (int i = 0; i < SIZE_OF_MANTISSA; i++) {
    sum_two_bit(num1[0], num2[0], res, i, &next_digit);
  }

  for (int i = 0; i < SIZE_OF_MANTISSA; i++) {
    sum_two_bit(num1[1], num2[1], res + 1, i, &next_digit);
  }

  sum_two_bit(num1[1], num2[1], res + 1, index_sign_bit, &next_digit);
}

int add_mantissa_big_with_twos_compliment(s21_decimal num1[2],
                                          s21_decimal num2[2],
                                          s21_decimal res[2]) {
  big_dec_twos_compliment(num1);
  big_dec_twos_compliment(num2);

  add_mantissa_big(num1, num2, res);

  int sign1 = big_dec_getsign(num1);
  int sign2 = big_dec_getsign(num2);
  int sign3 = big_dec_getsign(res);

  if (sign1 == sign2 && sign1 == 0 && sign3 == 1) {
    return err_code_arithmetic_too_large_or_inf;
  } else if (sign1 == sign2 && sign1 == 1 && sign3 == 0) {
    return err_code_arithmetic_too_small_or_negative_inf;
  }

  if (big_dec_getsign(res)) big_dec_twos_compliment(res);
  big_dec_twos_compliment(num1);
  big_dec_twos_compliment(num2);
  return err_code_arithmetic_no_err;
}

int big_dec_base_add(s21_decimal num1[2], s21_decimal num2[2],
                     s21_decimal res[2]) {
  return add_mantissa_big_with_twos_compliment(num1, num2, res);
}
