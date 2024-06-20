#include "../s21_decimal.h"

int left_shift(s21_decimal *num, int shift) {
  if (shift < 0) shift = 0;

  int err_code = err_code_no_err;
  int sign = getsign(*num);
  int dec_len = dec_num_len(*num);
  if ((dec_len + shift) > SIZE_OF_MANTISSA) {
    if (sign) {
      err_code = err_code_arithmetic_too_small_or_negative_inf;
    } else {
      err_code = err_code_arithmetic_too_large_or_inf;
    }
  }

  for (int i = SIZE_OF_MANTISSA - 1; i >= shift; i--) {
    int bit = getbit(*num, i - shift);
    setbit(num, i, bit);
  }
  for (int i = 0; i < shift; i++) {
    setbit(num, i, 0);
  }

  return err_code;
}