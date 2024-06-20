#include "../s21_decimal.h"

int mantissa_is_equal(s21_decimal num1, s21_decimal num2) {
  int res = 1;
  for (int i = 0; i < header_bit; i++) {
    res &= (num1.bits[i] == num2.bits[i]);
  }
  return res;
}

int s21_is_equal(s21_decimal num1, s21_decimal num2) {
  int res = 1;
  int sign1 = getsign(num1);
  int sign2 = getsign(num2);
  int scale_num1 = getscale(num1);
  int scale_num2 = getscale(num2);

  if (sign1 == sign2) {
    if (scale_num1 != scale_num2) {
      normalization(num1, num2, &num1, &num2);
    }
    res = mantissa_is_equal(num1, num2);
  } else if (is_zero(num1) && is_zero(num2)) {
    res = 1;
  } else {
    res = 0;
  }

  return res;
}

/* big decimal */

int big_dec_mantissa_is_equal(s21_decimal num1[2], s21_decimal num2[2]) {
  int res = 1;
  for (int i = 0; i < header_bit; i++) {
    res &= ((num1[0]).bits[i] == (num2[0]).bits[i]);
  }
  for (int i = 0; i < header_bit; i++) {
    res &= ((num1[1]).bits[i] == (num2[1]).bits[i]);
  }
  return res;
}
