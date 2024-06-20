#include "../s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int error = 0;
  if (dst && src != s21_INFINITY && src != s21_NAN) {
    init_num(dst);
    if (src < 0) {
      setsign(dst, 1);
      src = (-1) * src;
    } else if (src >= 0) {
      setsign(dst, 0);
    }
    if (src > INT_MAX)
      error = 1;
    else
      dst->bits[0] = src;
  } else
    error = 1;
  return error;
}
