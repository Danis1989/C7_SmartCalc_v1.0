#include "../s21_decimal.h"

void set_zero_header_bit(s21_decimal *num) { num->bits[header_bit] = 0; }