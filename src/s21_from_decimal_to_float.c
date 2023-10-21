#include "s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int res = 1;

  int error = 0;
  error = s21_is_owerflow_decimal(src);
  if (error != 0) return 1;
  error = s21_check_exponenta(src, src);
  if (error != 0) return 1;

  double temp = 0;
  char temp_s[100] = {0};
  float temp_f = 0;
  if (dst != NULL) {
    for (int i = 0; i < 96; i++) {
      temp += (s21_get_bit(src, i)) * (pow(2, i));
    }
    sprintf(temp_s, "%+e", temp);
    sscanf(temp_s, "%e", &temp_f);
    *dst = temp_f / pow(10, s21_get_exp(src));
    if (s21_get_bit(src, 127) == 1) *dst *= -1;
    res = 0;
  } else
    res = 1;

  return res;
}
