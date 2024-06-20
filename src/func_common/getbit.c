#include "../s21_decimal.h"

int getbit(s21_decimal num, int index) {
  if (index < 0 || index >= SIZE_OF_DEC) return err_incorrect_index;
  int byte_index = index / SIZE_OF_MINT;
  int bit_index = index % SIZE_OF_MINT;
  return (num.bits[byte_index] & (1 << bit_index)) > 0;
}
