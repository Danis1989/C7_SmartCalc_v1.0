#include "../s21_decimal.h"

void big_dec_setsign(s21_decimal num[2], int sign) {
  sign = sign ? 1 : 0;
  setbit(num + 1, index_sign_bit, sign);
}