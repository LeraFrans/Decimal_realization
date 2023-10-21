#include "s21_decimal.h"

// from oleja
int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int res = 0;
  if (s21_compare_decimal(value_1, value_2) == 0) res = 1;
  return res;
}

// Returned:
//  0 - equal
//  1 - first decimal is greater
//  2 - first decimal is less
//  -1 - error
int s21_compare_decimal(s21_decimal value_1, s21_decimal value_2) {
  int res = 1;

  int flag_equal = 1;
  for (int i = 0; i < 4; i++) {
    if (value_1.bits[i] != value_2.bits[i]) {
      flag_equal = 0;
      break;
    }
  }
  if (flag_equal == 1) return 0;

  if (s21_check_exponenta(value_1, value_2) != 0) return -1;

  int sign_1 = s21_get_bit(value_1, 127);
  int sign_2 = s21_get_bit(value_2, 127);

  // printf("sig_1 = %d   sign_2 = %d\n", sign_1, sign_2);

  if (sign_1 == 0 && sign_2 == 1)
    return 1;
  else if (sign_1 == 1 && sign_2 == 0)
    return 2;

  s21_big_decimal big_1 = {0};
  s21_big_decimal big_2 = {0};
  s21_cpy_decimal_to_big_decimal(value_1, &big_1);
  s21_cpy_decimal_to_big_decimal(value_2, &big_2);
  int array_1[90] = {0};
  int array_2[90] = {0};
  s21_from_big_decimal_to_ten_array(big_1, array_1);
  s21_from_big_decimal_to_ten_array(big_2, array_2);
  int exp_1 = s21_get_exp(value_1);
  int exp_2 = s21_get_exp(value_2);

  // printf("big_1 in start\n");
  // s21_print_big_ten_array(array_1);
  // printf("big_2 in start\n");
  // s21_print_big_ten_array(array_2);

  // printf("Exp_1 = %d   Exp_2 = %d\n", exp_1, exp_2);

  int difference = exp_1 - exp_2;

  // printf("Difference = %d\n", difference);

  if (difference > 0) {
    for (int i = 0; i < difference; i++) {
      for (int j = 89; j > 0; j--) array_2[j] = array_2[j - 1];
      array_2[0] = 0;
    }
  } else if (difference < 0) {
    for (int i = 0; i < -difference; i++) {
      // printf("i = %d\n", i);
      for (int j = 89; j > 0; j--) array_1[j] = array_1[j - 1];
      array_1[0] = 0;
    }
  }

  // printf("big_1 after normalization\n");
  // s21_print_big_ten_array(array_1);
  // printf("big_2 after normalization\n");
  // s21_print_big_ten_array(array_2);

  int compare = s21_compare_big_ten_array(array_1, array_2);
  if ((compare == 1 && sign_1 == 0) || (compare == -1 && sign_1 == 1))
    res = 1;
  else if ((compare == -1 && sign_1 == 0) || (compare == 1 && sign_1 == 1))
    res = 2;
  else if (compare == 0)
    res = 0;

  return res;
}