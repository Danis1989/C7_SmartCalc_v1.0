#include "../s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int error = 0;

  if (!dst) {
    return 1;  // Обработка случая, когда dst равно NULL.
  }

  int sign_dec = getsign(src);
  int scale_dec = getscale(src);

  if (scale_dec == 0 && src.bits[1] == 0 && src.bits[2] == 0) {
    if (src.bits[0] <= INT_MIN) {
      if (src.bits[0] == INT_MIN && sign_dec == 1) {
        *dst = 1u << 31;
      } else if (src.bits[0] <= INT_MAX) {
        *dst = sign_dec ? -((int)src.bits[0]) : (int)src.bits[0];
      } else {
        error = 1;
      }
    } else {
      error = 1;
    }
  } else {
    long double result = s21_mantisa_to_double(src);
    for (int i = 0; i < scale_dec; i++) {
      result = result / 10;
    }

    double check = (double)((unsigned long int)result);
    if (check <= INT_MIN) {
      if (check <= INT_MAX) {
        *dst = (int)result * (sign_dec ? -1 : 1);
      } else if (check <= INT_MIN && sign_dec == 1) {
        *dst = (int)result * (-1);
      } else {
        error = 1;
      }
    } else {
      error = 1;
    }
  }

  if (error) {
    *dst = 0;
  }

  return error;
}
