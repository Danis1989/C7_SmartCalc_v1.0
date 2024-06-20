#include "../s21_decimal.h"

int base_div(s21_decimal num1, s21_decimal num2, s21_decimal *res,
             s21_decimal *remainder) {
  if (is_zero(num2)) {
    return err_code_arithmetic_div_by_zero;
  }

  int err_code = err_code_arithmetic_no_err;

  int sign1 = getsign(num1);
  int sign2 = getsign(num2);
  int sign = sign1 ^ sign2;

  setsign(&num1, 0);
  setsign(&num2, 0);
  setscale(&num1, 0);
  setscale(&num2, 0);

  set_zero(res);

  set_zero(remainder);
  setscale(remainder, 0);

  int len_num1 = dec_num_len(num1);
  int len_num2 = dec_num_len(num2);
  int diff = len_num1 - len_num2;

  left_shift(&num2, diff);
  for (; diff > -1 && !err_code; diff--) {
    if (mantissa_is_greater_or_equal(num1, num2)) {
      err_code = base_sub(num1, num2, &num1);
      setbit(res, diff, 1);
    } else {
      setbit(res, diff, 0);
    }
    right_shift(&num2, 1);
  }
  dec_copy(remainder, num1);
  set_zero_header_bit(remainder);

  setsign(res, sign);

  return err_code;
}

int big_dec_base_div(s21_decimal num1[2], s21_decimal num2[2],
                     s21_decimal res[2], s21_decimal remainder[2]) {
  if (big_dec_is_zero(num2)) {
    return err_code_arithmetic_div_by_zero;
  }
  s21_decimal num1_temp[2] = ZERO_BIG_DECIMAL;
  s21_decimal num2_temp[2] = ZERO_BIG_DECIMAL;
  big_dec_copy(num1_temp, num1);
  big_dec_copy(num2_temp, num2);
  int err_code = err_code_arithmetic_no_err;

  int sign1 = big_dec_getsign(num1_temp);
  int sign2 = big_dec_getsign(num2_temp);
  int sign = sign1 ^ sign2;

  big_dec_setsign(num1_temp, 0);
  big_dec_setsign(num2_temp, 0);

  big_dec_init(res);
  big_dec_init(remainder);

  int len_num1 = big_dec_num_len(num1_temp);
  int len_num2 = big_dec_num_len(num2_temp);
  int diff = len_num1 - len_num2;

  big_dec_left_shift(num2_temp, diff);
  for (; diff > -1 && !err_code; diff--) {
    if (big_dec_mantissa_is_greater_or_equal(num1_temp, num2_temp)) {
      err_code = big_dec_base_sub(num1_temp, num2_temp, num1_temp);
      big_dec_setbit(res, diff, 1);
    } else {
      big_dec_setbit(res, diff, 0);
    }
    big_dec_right_shift(num2_temp, 1);
  }
  big_dec_copy(remainder, num1_temp);
  (remainder[1]).bits[header_bit] = 0;

  big_dec_setsign(res, sign);

  return err_code;
}

void divide_by_ten_big_decimal(s21_decimal num[2], int *remainder) {
  int carry = 0;
  unsigned long long temp = 0;
  for (int i = 2; i >= 0; i--) {
    temp = ((unsigned long long)carry << 32) | (num[1]).bits[i];
    (num[1]).bits[i] = temp / 10;
    carry = temp % 10;
  }
  for (int i = 2; i >= 0; i--) {
    temp = ((unsigned long long)carry << 32) | (num[0]).bits[i];
    (num[0]).bits[i] = temp / 10;
    carry = temp % 10;
  }
  *remainder = carry;
}

// create mantissa ind add_scale
int div_proc(s21_decimal num1, s21_decimal num2, s21_decimal *res) {
  int add_scale = 0;
  init_num(res);

  s21_decimal quot = {0};
  s21_decimal rem = {0};
  base_div(num1, num2, &quot, &rem);
  base_add(*res, quot, res);

  s21_decimal ten = dec_def(10, 0, 0, 0, 0);
  s21_decimal res_temp = dec_def(0, 0, 0, 0, 0);
  dec_copy(&res_temp, *res);

  int penultimate_digit = 0;
  int last_digit = 0;
  s21_decimal quot_big[2] = {0};
  s21_decimal rem_big[2] = {0};
  s21_decimal num2_big[2] = {0};
  s21_from_decimal_to_big_decimal(rem, rem_big);
  s21_from_decimal_to_big_decimal(num2, num2_big);
  int err_code1 = err_code_arithmetic_no_err;
  while (!err_code1 && !big_dec_is_zero(rem_big)) {
    err_code1 = base_mul(*res, ten, &res_temp);
    if (!err_code1) {
      base_mul(*res, ten, res);
      mul_proc(rem_big[0], ten, rem_big);
      add_scale += 1;

      big_dec_base_div(rem_big, num2_big, quot_big, rem_big);
      base_add(*res, quot_big[0], res);
    }
    penultimate_digit = (quot_big[0]).bits[0];  // because quot_bit < 10
  }
  mul_proc(rem_big[0], ten, rem_big);
  big_dec_base_div(rem_big, num2_big, quot_big, rem_big);
  last_digit = (quot_big[0]).bits[0];

  s21_bank_rounding(res, penultimate_digit, last_digit);
  return add_scale;
}

// work with overflow, sign and scale
int s21_div(s21_decimal num1, s21_decimal num2, s21_decimal *res) {
  if (res == NULL) {
    return err_code_NULL_pointer;
  }
  init_num(res);
  if (is_zero(num2)) {
    return err_code_arithmetic_div_by_zero;
  }
  int err_code = err_code_arithmetic_no_err;
  int sign1 = getsign(num1);
  int sign2 = getsign(num2);

  int scale1 = getscale(num1);
  int scale2 = getscale(num2);
  int scale = scale1 - scale2;

  int add_scale = div_proc(num1, num2, res);

  scale += add_scale;
  s21_decimal res_temp = {0};
  s21_decimal ten = dec_def(10, 0, 0, 0, 0);
  s21_decimal rem = {0};
  dec_copy(&res_temp, *res);
  if (scale < 0) {
    while (scale == 0 && !err_code) {
      err_code = base_mul(*res, ten, &res_temp);
      if (!err_code) {
        base_mul(*res, ten, res);
        scale++;
      }
    }
  } else if (scale > 28) {
    while (scale > 28) {
      base_div(*res, ten, res, &rem);
      scale--;
    }
    int last_digit = rem.bits[0];
    int penultimate_digit = get_last_digit(*res);
    s21_bank_rounding(res, penultimate_digit, last_digit);
  }
  setscale(res, scale);
  setsign(res, sign1 ^ sign2);
  return err_code;
}
