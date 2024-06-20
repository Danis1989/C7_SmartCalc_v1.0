#include "../s21_decimal.h"

int base_mul(s21_decimal num1, s21_decimal num2, s21_decimal *res) {
  set_zero(res);

  int shift = 0;
  int err_code = err_code_arithmetic_no_err;
  int err_var_temp1 = err_code_arithmetic_no_err;
  int err_var_temp2 = err_code_arithmetic_no_err;
  for (int i = 0; i < SIZE_OF_MANTISSA && !err_code; i++) {
    int bit = getbit(num2, i);
    if (bit) {
      err_var_temp1 = left_shift(&num1, i - shift);
      shift = i;
      err_var_temp2 = base_add(num1, *res, res);

      // Можно было и в другом порядке
      if (err_var_temp1) {
        err_code = err_var_temp1;
      } else if (err_var_temp2) {
        err_code = err_var_temp2;
      }
    }
  }

  int sign1 = getsign(num1);
  int sign2 = getsign(num2);
  int sign = sign1 ^ sign2;
  setsign(res, sign);

  return err_code;
}

void mul_proc(s21_decimal num1, s21_decimal num2, s21_decimal res_big[2]) {
  s21_decimal divisor = {{0, 0x10000, 0, 0}};  // 2^48

  s21_decimal num1_quot = {0};  // quotient
  s21_decimal num2_quot = {0};
  s21_decimal num1_rem = {0};  // remainder
  s21_decimal num2_rem = {0};
  s21_decimal parts[4] = {0};

  base_div(num1, divisor, &num1_quot, &num1_rem);
  base_div(num2, divisor, &num2_quot, &num2_rem);

  base_mul(num1_quot, num2_quot, &(parts[0]));
  base_mul(num1_quot, num2_rem, &(parts[1]));
  base_mul(num1_rem, num2_quot, &(parts[2]));
  base_mul(num1_rem, num2_rem, &(parts[3]));

  s21_decimal part1_big[2] = {parts[0], {{0, 0, 0, 0}}};
  s21_decimal part2_big[2] = {parts[1], {{0, 0, 0, 0}}};
  s21_decimal part3_big[2] = {parts[2], {{0, 0, 0, 0}}};
  s21_decimal part4_big[2] = {parts[3], {{0, 0, 0, 0}}};

  big_dec_left_shift(part1_big, 96);
  big_dec_left_shift(part2_big, 48);
  big_dec_left_shift(part3_big, 48);

  add_mantissa_big(part1_big, part2_big, res_big);
  add_mantissa_big(res_big, part3_big, res_big);
  add_mantissa_big(res_big, part4_big, res_big);
}

int s21_mul(s21_decimal num1, s21_decimal num2, s21_decimal *res) {
  if (res == NULL) {
    return err_code_NULL_pointer;
  }
  init_num(res);
  int err_code = err_code_arithmetic_no_err;

  int sign1 = getsign(num1);
  int sign2 = getsign(num2);
  int sign = sign1 ^ sign2;

  s21_decimal res_big[2] = {0};
  mul_proc(num1, num2, res_big);

  int scale = getscale(num1) + getscale(num2);
  int last_digit = 0;
  while ((!is_zero(res_big[1]) && scale > 0) || scale > 28) {
    divide_by_ten_big_decimal(res_big, &last_digit);
    scale--;
  }
  int penultimate_digit = big_dec_get_last_digit(res_big);

  // bank rounding
  s21_decimal one_big[2] = ONE_BIG_DECIMAL;
  if (penultimate_digit % 2 == 0 && last_digit > 5) {  // <--
    add_mantissa_big(res_big, one_big, res_big);
  } else if (penultimate_digit % 2 == 1 && last_digit >= 5) {
    add_mantissa_big(res_big, one_big, res_big);
  }

  setscale(&res_big[0], scale);
  dec_copy(res, res_big[0]);
  setsign(res, sign);

  if (!scale && !is_zero(res_big[1]) && !sign) {
    err_code = err_code_arithmetic_too_large_or_inf;
  } else if (!scale && !is_zero(res_big[1]) && sign) {
    err_code = err_code_arithmetic_too_small_or_negative_inf;
  }
  return err_code;
}