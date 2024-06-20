#include "../s21_decimal.h"

void set_zero(s21_decimal *num) {
  for (int i = 0; i < NUMBER_OF_MINTS_MANTISSA; i++) {
    num->bits[i] = 0;
  }
}
