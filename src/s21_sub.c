#include"s21_decimal.h"

#define U_MAX_INT 4294967295



int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {

    //меняем знак второго вычетаемого числа
    if (s21_get_bit(value_2, 127) == 1) s21_set_bit_V2(&value_2, 127, 0);
    else s21_set_bit_V2(&value_2, 127, 1);
    int res = s21_add(value_1, value_2, result);
    return res;
}