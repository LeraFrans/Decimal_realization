#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int res = OK;
  if (src == INFINITY || src == -INFINITY) return 1;
  s21_decimal dcml = {0};
  if (dst != NULL) {
    for (int i = 0; i < 4; i++) dst->bits[i] = 0;

    if (src < 0) {
      s21_set_bit(dcml, dst, 127);  // set sign bit
      src *= -1;
    }
    dst->bits[0] = src;
  } else
    res = NULL_POINTER_EXEPTION;

  return res;
}
