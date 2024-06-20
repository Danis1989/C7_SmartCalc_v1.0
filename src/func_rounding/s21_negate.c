#include "../s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  *result = value;
  setsign(result, !getsign(value));
  return 0;
}