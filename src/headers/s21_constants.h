#ifndef S21_STRUCTS_H_
#define S21_STRUCTS_H_

#include <stdint.h>

#define SET_BIT(num, index) (num |= 1 << index)
#define RESET_BIT(num, index) (num &= ~(1 << index))

#define INT_MAX 2147483647
#define INT_MIN 2147483648

#define s21_INFINITY (1.0 / 0.0)
#define s21_NAN (0.0 / 0.0)

#define NUMBER_OF_MINTS 4
#define NUMBER_OF_MINTS_MANTISSA 3
#define SIZE_OF_MINT 32
#define SIZE_OF_MANTISSA 96
#define SIZE_OF_DEC 128
#define is_fin(x) __builtin_isfinite(x)
#define is_nan(x) __builtin_isnan(x)
#define is_inf(x) __builtin_isinf(x)
typedef enum { CONVERTATION_OK, CONVERTATION_ERROR } conv_res;
#define TRICKY_LOOP \
  while (pos >= 0 && int_str[pos] == '0') int_str[pos--] = '\0';

#define MAX_SCALE 28
#define SCALE_MASK 0xFF
#define SCALE_CLR_MASK 0xFF00FFFF

/* This project will use int and mint data types */
typedef uint32_t mint;  // My int
/* Use mint to work with decimal bits */

typedef struct {
  mint bits[NUMBER_OF_MINTS];
} s21_decimal;

typedef enum {
  index_start_exp_bits = 16,
  index_end_exp_bits = 23,
  index_sign_bit = 127
} index_of_dec_num;

typedef enum {
  big_dec_index_sign_bit = 255,
} index_of_big_dec_num;

typedef enum {
  first_bit = 0,
  second_bit = 1,
  third_bit = 2,
  header_bit = 3
} index_bits;

typedef enum {
  err_incorrect_index = -1,
  err_code_no_err = 0,
  err_code_num_is_too_small_or_great = 1,
  err_code_scale_is_too_small_or_great = 2,
  err_code_loss_info = 3,
  err_code_incorrect_number_system = 4,
  err_code_NULL_pointer = 5,
} err_code;

/*return constants for main functions*/
typedef enum {
  err_code_arithmetic_no_err = 0,
  err_code_arithmetic_too_large_or_inf = 1,
  err_code_arithmetic_too_small_or_negative_inf = 2,
  err_code_arithmetic_div_by_zero = 3
} err_code_arithmetic;

typedef enum {
  return_value_comparison_false = 0,
  return_value_comparison_true = 1
} return_value_comparison;

typedef enum {
  err_code_conversion_no_err = 0,
  err_code_conversion_error = 1
} err_code_conversion;

typedef enum {
  err_code_rounding_no_err = 0,
  err_code_rounding_error = 1
} err_code_rounding;
/*-----------------------------------*/

#endif  // S21_STRUCTS_H_