#include "../s21_decimal.h"

void div_ten(s21_decimal *value) {
  unsigned long long int last = value->bits[2];
  unsigned int remainder = 0;
  for (int i = 2; i >= 0; i--) {
    remainder = last % 10;
    value->bits[i] = last / 10;
    last = remainder * (4294967296) + value->bits[i - 1];
  }
}