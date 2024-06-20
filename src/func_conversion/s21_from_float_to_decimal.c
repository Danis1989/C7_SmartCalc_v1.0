#include "../s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  bool flag_minus = 0;

  if (dst && !is_inf(src) && !is_nan(src)) {
    set_zero(dst);
    if (src < 0) src *= -1.0f, flag_minus = 1;
    float fl_int = 0.0;

    float fl_fract = modff(src, &fl_int);
    int whole = s21_from_float_string((int)fl_int, fl_fract, dst);
    int scale_temp = getscale(*dst);

    s21_from_int_to_decimal(whole, dst);
    setscale(dst, scale_temp);
    if (flag_minus) setbit(dst, 127, 1);
  } else {
    set_zero(dst);
    return CONVERTATION_ERROR;
  }

  return CONVERTATION_OK;
}

int s21_from_float_string(int whole, float fract, s21_decimal *value) {
  char fr_str[255] = {0};
  char int_str[255] = {0};
  int pos = 0;
  int exp = 0;

  if (fract != 0.0) sprintf(fr_str, "%.9f", fract);
  if (whole != 0.0) sprintf(int_str, "%d", whole);
  memmove(fr_str, fr_str + 2, strlen(fr_str));
  exp = strlen(int_str);
  strcat(int_str, fr_str);

  size_t pos_sign_number = strlen(int_str);
  pos = pos_sign_number;

  if (pos_sign_number > 7 && strlen(fr_str) > 0) {
    while (pos != 7) int_str[pos--] = '\0';
    if ((int)int_str[pos] - '0' > 4) {
      pos--;
      if (int_str[pos] == '9') {
        while (int_str[pos] == '9') int_str[pos--] = '0';
        int_str[pos]++;
      } else
        int_str[pos]++;

      int_str[7] = '\0';
      pos = strlen(int_str) - 1;
      TRICKY_LOOP
    } else
      TRICKY_LOOP
  }
  exp = (strlen(int_str) - exp);
  setscale(value, exp);

  return atoi(int_str);
}