#include "../s21_decimal.h"

// num1 > num2 ????

int mantissa_is_greater(s21_decimal num1, s21_decimal num2) {
  int index = 0, res = 0, flag = 0;
  int sign1 = getsign(num1);
  int sign2 = getsign(num2);

  if (sign1 > sign2) {
    res = 0;
  } else if (sign1 < sign2 && !(is_zero(num1) && is_zero(num2))) {
    res = 1;
  }

  if (sign1 == sign2) {
    for (index = 2; index >= 0 && !flag; index--) {
      if (num1.bits[index] > num2.bits[index]) {
        res = 1;
        flag = 1;
      } else if (num1.bits[index] < num2.bits[index]) {
        flag = 1;
      }
    }

    if (sign1 == 1 && flag) res = !res;
  }

  return res;
}

int s21_is_greater(s21_decimal num1, s21_decimal num2) {
  if (getscale(num2) != getscale(num1)) {
    normalization(num1, num2, &num1, &num2);
  }
  return mantissa_is_greater(num1, num2);
}

/* big decimal */

int big_dec_mantissa_is_greater(s21_decimal num1[2], s21_decimal num2[2]) {
  int index = 0, res = 0, flag = 0;
  int sign1 = big_dec_getsign(num1);
  int sign2 = big_dec_getsign(num2);

  if (sign1 > sign2) {
    res = 0;
  } else if (sign1 < sign2 &&
             !(big_dec_is_zero(num1) && big_dec_is_zero(num2))) {
    res = 1;
  }

  if (sign1 == sign2) {
    for (index = 5; index >= 0 && !flag; index--) {
      int big_index = index / 3;
      int dec_index = index % 3;
      if ((num1[big_index]).bits[dec_index] >
          (num2[big_index]).bits[dec_index]) {
        res = 1;
        flag = 1;
      } else if ((num1[big_index]).bits[dec_index] <
                 (num2[big_index]).bits[dec_index]) {
        flag = 1;
      }
    }

    if (sign1 == 1 && flag) res = !res;
  }

  return res;
}