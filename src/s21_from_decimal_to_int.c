#include "s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int res = 0;
  int error = 0;
  error = s21_is_owerflow_decimal(src);
  if (error != 0) return 1;
  error = s21_check_exponenta(src, src);
  if (error != 0) return 1;

  int array[30] = {0};
  s21_from_decimal_to_ten_array(src, array);
  int exp = s21_get_exp(src);
  int sign = s21_get_bit(src, 127);
  int int_array[30] = {0};
  for (int i = exp; i < 30; i++) int_array[i - exp] = array[i];

  int max_int_array[] = {7, 4, 6, 3, 8, 4, 7, 4, 1, 2, 0, 0, 0, 0, 0,
                         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  if (s21_compare_ten_array(int_array, max_int_array) == 1)
    res = 1;
  else {
    s21_decimal tmp = {0};
    s21_from_ten_array_to_decimal(int_array, &tmp);
    *dst = tmp.bits[0];
    if (sign) *dst = -*dst;
  }
  return res;
}