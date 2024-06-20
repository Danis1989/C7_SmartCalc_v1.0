#include "../s21_decimal.h"

s21_decimal dec_def(mint bits1, mint bits2, mint bits3, int scale, int sign) {
  s21_decimal num = {{bits1, bits2, bits3, 0}};
  setscale(&num, scale);
  setsign(&num, sign);
  return num;
}