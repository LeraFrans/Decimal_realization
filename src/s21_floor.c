#include "s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  int res = 0;
  //тут всякие разные проверки
  int error = 0;
  error = s21_is_owerflow_decimal(value);
  if (error != 0) return 1;
  error = s21_check_exponenta(value, value);
  if (error != 0) return 1;

  result->bits[0] = 0;
  result->bits[1] = 0;
  result->bits[2] = 0;

  int sign = s21_get_bit(value, 127);
  int array[30] = {0};
  s21_from_decimal_to_ten_array(value, array);
  int exp = 0;
  exp = s21_get_exp(value);
  int flag_remaind = 0;
  for (int i = 0; i < exp; i++) {
    if (array[0] != 0) flag_remaind = 1;
    for (int i = 0; i < 29; i++) array[i] = array[i + 1];
    array[29] = 0;
  }

  int one[30] = {0};
  one[0] = 1;
  if (flag_remaind == 1 && sign == 1) {
    s21_sum_of_ten_array(array, one);
  }

  s21_from_ten_array_to_decimal(array, result);

  result->bits[3] = 0;
  s21_set_bit_V2(result, 127, sign);

  return res;
}