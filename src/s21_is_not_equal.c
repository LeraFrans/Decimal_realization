#include "s21_decimal.h"

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  int res = 0;
  if (s21_compare_decimal(value_1, value_2) != 0) res = 1;
  return res;
}