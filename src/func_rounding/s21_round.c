#include "../s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  s21_decimal five = {{5, 0, 0, 0}};
  setscale(&five, 1);
  if (getscale(value) != 0) {
    s21_add(value, five, result);
    s21_truncate(*result, result);
  } else {
    (*result) = value;
  }
  return 0;
}
