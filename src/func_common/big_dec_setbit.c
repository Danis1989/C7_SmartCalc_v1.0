#include "../s21_decimal.h"

void big_dec_setbit(s21_decimal num[2], int index, int bit) {
  bit = bit ? 1 : 0;
  int big_dec_index = index / SIZE_OF_MANTISSA;
  int dec_index = index % SIZE_OF_MANTISSA;

  if (big_dec_index == 0) {
    setbit(num, dec_index, bit);
  } else {
    setbit(num + 1, dec_index, bit);
  }
}
