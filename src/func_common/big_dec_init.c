#include "../s21_decimal.h"

void big_dec_init(s21_decimal num_big[2]) {
  for (int i = 0; i < NUMBER_OF_MINTS; i++) {
    (num_big[0]).bits[i] = 0;
  }
  for (int i = 0; i < NUMBER_OF_MINTS; i++) {
    (num_big[1]).bits[i] = 0;
  }
}