#include "s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
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
  int exp = 0;
  exp = s21_get_exp(value);
  int remainder = 0;
  for (int i = 0; i < exp; i++) {
    remainder = array[0];
    for (int i = 0; i < 29; i++) array[i] = array[i + 1];
    array[29] = 0;
  }

  int one[30] = {0};
  one[0] = 1;
  if (remainder >= 5) {
    s21_sum_of_ten_array(array, one);
  }

  s21_from_ten_array_to_decimal(array, result);

  result->bits[3] = 0;
  s21_set_bit_V2(result, 127, sign);

  return res;
}

int s21_is_owerflow_decimal(s21_decimal value) {
  int res = 0;

  if (value.bits[0] == INFINITY || value.bits[1] == INFINITY ||
      value.bits[2] == INFINITY) {
    if (s21_get_bit(value, 127) == 0)
      res = 1;
    else
      res = 2;
  }

  return res;
}

// //изменяет сам децимал (отсекает дробную часть), возвращает число, равное
// //последней отсеченной цифре
// int s21_rounds_and_remember_remaind(s21_decimal *value) {
//   int array[30] = {0};
//   s21_from_decimal_to_ten_array(*value, array);

//   int exp = 0;
//   exp = s21_get_exp(*value);

//   int remainder = 0;
//   for (int i = 0; i < exp; i++) {
//     exp--;
//     remainder = array[0];
//     for (int i = 0; i < 29; i++) array[i] = array[i + 1];
//     array[29] = 0;
//   }

//   s21_from_ten_array_to_decimal(array, value);

//   return remainder;
// }