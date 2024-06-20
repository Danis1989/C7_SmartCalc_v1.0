#include "../s21_decimal.h"

int big_dec_getsign(s21_decimal num[2]) {
  return getbit(num[1], index_sign_bit);
}
