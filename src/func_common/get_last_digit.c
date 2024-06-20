#include "../s21_decimal.h"

int get_last_digit(s21_decimal num) {
  s21_decimal devisor = TEN_DECIMAL;
  s21_decimal remainder = {0};
  base_div(num, devisor, &num, &remainder);
  return remainder.bits[0];
}