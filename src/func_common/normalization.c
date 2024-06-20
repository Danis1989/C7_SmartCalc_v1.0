#include "../s21_decimal.h"

int normalization_proc(s21_decimal num1, s21_decimal num2,
                       s21_decimal *num1_norm, s21_decimal *num2_norm) {
  int err_code = err_code_no_err;

  dec_copy(num1_norm, num1);
  dec_copy(num2_norm, num2);

  // scale1 <= scale2
  int scale1 = getscale(num1);
  int scale2 = getscale(num2);

  s21_decimal ten_d = TEN_DECIMAL;
  s21_decimal remainder = {0};
  s21_decimal temp = {0};
  while (scale1 != scale2) {
    int is_possible_to_mul = !(base_mul(*num1_norm, ten_d, &temp));
    if (is_possible_to_mul) {
      base_mul(*num1_norm, ten_d, num1_norm);
      setscale(num1_norm, ++scale1);
    } else {
      base_div(*num2_norm, ten_d, num2_norm, &remainder);
      setscale(num2_norm, --scale2);
      err_code = err_code_loss_info;
    }
  }

  // bank rounding
  int is_possible_to_mul = !(base_mul(*num1_norm, ten_d, &temp));
  if (!is_possible_to_mul) {
    int last_digit = remainder.bits[0];
    int penultimate_digit = get_last_digit(*num2_norm);
    s21_decimal term = ONE_DECIMAL;
    if (penultimate_digit % 2 == 0 && last_digit > 5) {  // <--
      if (!getsign(*num2_norm)) {
        base_add(*num2_norm, term, num2_norm);
      } else {
        base_sub(*num2_norm, term, num2_norm);
      }
    }
    if (penultimate_digit % 2 == 1 && last_digit >= 5) {
      if (!getsign(*num2_norm)) {
        base_add(*num2_norm, term, num2_norm);
      } else {
        base_sub(*num2_norm, term, num2_norm);
      }
    }
  }

  return err_code;
}

int normalization(s21_decimal num1, s21_decimal num2, s21_decimal *num1_norm,
                  s21_decimal *num2_norm) {
  int err_code = err_code_no_err;
  int scale1 = getscale(num1);
  int scale2 = getscale(num2);
  if (scale1 <= scale2) {
    err_code = normalization_proc(num1, num2, num1_norm, num2_norm);
  } else {
    err_code = normalization_proc(num2, num1, num2_norm, num1_norm);
  }
  return err_code;
}