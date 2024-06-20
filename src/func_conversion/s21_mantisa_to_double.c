#include "../s21_decimal.h"

double s21_mantisa_to_double(s21_decimal src) {
  double result = 0;
  double scale = 1;
  for (int i = 0; i < NUMBER_OF_MINTS_MANTISSA; i++) {
    result += ((double)src.bits[i] * scale);
    scale *= 4294967296;
  }
  return result;
}