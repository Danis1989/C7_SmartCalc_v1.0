#include "../s21_decimal.h"

int getscale(s21_decimal num) {
  return (int)(num.bits[header_bit] >> index_start_exp_bits) & SCALE_MASK;
}
