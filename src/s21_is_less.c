#include "s21_decimal.h"

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  int res = 0;
  if (s21_compare_decimal(value_1, value_2) == 2) res = 1;
  return res;
}