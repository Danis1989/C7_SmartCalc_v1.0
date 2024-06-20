#include "../s21_decimal.h"

void init_num(s21_decimal* num) {
  for (int i = 0; i < 128; i++) {
    setbit(num, i, 0);
  }
}