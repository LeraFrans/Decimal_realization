#include "s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int res = 0;
  //тут всякие разные проверки
  int error = 0;
  error = s21_is_owerflow_decimal(value);
  if (error != 0) return 1;
  error = s21_check_exponenta(value, value);
  if (error != 0) return 1;

  int sign = s21_get_bit(value, 127);
  int array[30] = {0};
  s21_from_decimal_to_ten_array(value, array);
  // print_ten_array(array);
  int exp = 0;
  exp = s21_get_exp(value);
  // printf("exp = %d\n", exp);
  for (int i = 0; i < exp; i++) {
    for (int i = 0; i < 29; i++) array[i] = array[i + 1];
    array[29] = 0;
  }

  s21_from_ten_array_to_decimal(array, result);

  result->bits[3] = 0;
  s21_set_bit_V2(result, 127, sign);

  return res;
}
