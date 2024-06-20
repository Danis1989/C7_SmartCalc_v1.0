#include "../s21_decimal.h"
int s21_truncate(s21_decimal value, s21_decimal *result) {
  int scale = getscale(value);
  *result = value;
  while (scale > 0) {
    div_ten(result);
    scale--;
  }
  setscale(result, 0);
  return 0;
}
