#include "../s21_decimal.h"

void right_shift(s21_decimal *num, int shift) {
  if (shift < 0) shift = 0;
  for (int i = 0; i < SIZE_OF_MANTISSA - shift; i++) {
    int bit = getbit(*num, i + shift);
    setbit(num, i, bit);
  }
  for (int i = 0; i < shift; i++) {
    setbit(num, SIZE_OF_MANTISSA - 1 - i, 0);
  }
}