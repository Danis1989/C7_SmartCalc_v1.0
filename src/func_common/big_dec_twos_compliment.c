#include "../s21_decimal.h"

void big_dec_twos_compliment(s21_decimal num[2]) {
  if (big_dec_getsign(num)) {
    s21_decimal one_big[2] = ONE_BIG_DECIMAL;

    for (int i = 0; i < NUMBER_OF_MINTS_MANTISSA; i++) {
      (num[0]).bits[i] = ~(num[0]).bits[i];
    }
    for (int i = 0; i < NUMBER_OF_MINTS_MANTISSA; i++) {
      (num[1]).bits[i] = ~(num[1]).bits[i];
    }
    add_mantissa_big(one_big, num, num);
  }
}