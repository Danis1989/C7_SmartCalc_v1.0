#include "../s21_decimal.h"

void setsign(s21_decimal *num, int sign) {
  sign = sign ? 1 : 0;
  setbit(num, index_sign_bit, sign);
}