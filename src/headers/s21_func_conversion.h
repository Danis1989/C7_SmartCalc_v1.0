#ifndef S21_FUNC_CONVERSION_H_
#define S21_FUNC_CONVERSION_H_

/*main conversion functions*/
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);
double s21_mantisa_to_double(s21_decimal src);
int s21_from_float_string(int whole, float fract, s21_decimal *value);

/* big decimal */

void s21_from_decimal_to_big_decimal(s21_decimal num, s21_decimal num_big[2]);

#endif  // S21_FUNC_CONVERSION_H_