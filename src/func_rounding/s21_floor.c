#include "../s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  s21_decimal minus_one = ONE_DECIMAL;
  s21_negate(minus_one, &minus_one);
  s21_truncate(value, result);
  if (getsign(value) == 1 &&
      s21_is_not_equal(
          value, *result)) {  //если число отрицательное и имеет дробную часть
    s21_add(*result, minus_one,
            result);  //                   прибавляем минус один
  }
  return 0;
}