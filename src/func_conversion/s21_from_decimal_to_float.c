#include "../s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int err_code = err_code_conversion_no_err;

  int sign = getsign(src);
  int scale = getscale(src);
  double res = s21_mantisa_to_double(src);

  if (scale == 0) {
    *dst = (float)res * (sign ? -1 : 1);

  } else if (scale <= 28 && scale > 0) {
    for (int i = 0; i < scale; i++) {
      res = res / 10;
    }
    *dst = (float)res * (sign ? -1 : 1);
  } else {
    *dst = 0;
    err_code = err_code_conversion_error;
  }
  return err_code;
}