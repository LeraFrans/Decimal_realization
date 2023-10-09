#include "s21_decimal.h"

/** @brief Subtracts two decimal, the result of the subtraction is writen into result
 *
 *
 *  @param value_1 first decimal
 *  @param value_2 second decimal
 *  @param result resulting decimal
 *  @return 0 - OK.  
            1 - the number is too large or equal to infinity.  
            2 - the number is too small or equal to negative infinity.  
 */
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  //меняем знак второго вычетаемого числа
  if (s21_get_bit(value_2, 127) == 1)
    s21_set_bit_V2(&value_2, 127, 0);
  else
    s21_set_bit_V2(&value_2, 127, 1);

  int res = s21_add(value_1, value_2, result);
  return res;
}