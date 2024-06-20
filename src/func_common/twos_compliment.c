#include "../s21_decimal.h"

s21_decimal twos_compliment(s21_decimal num) {
  if (!getsign(num)) return num;

  s21_decimal res = {0};
  s21_decimal one = {{1, 0, 0, 0}};

  for (int i = 0; i < NUMBER_OF_MINTS_MANTISSA; i++) {
    res.bits[i] = ~num.bits[i];
  }
  res.bits[header_bit] = num.bits[header_bit];
  add_mantissa(one, res, &res);
  return res;
}