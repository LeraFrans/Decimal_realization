#include "s21_decimal.h"

//Округляет указанное Decimal число до ближайшего целого числа в сторону отрицательной бесконечности.
//0 - OK
//1 - ошибка вычисления
int s21_floor(s21_decimal value, s21_decimal *result) {
    int array[30] = {0};
    s21_from_decimal_to_ten_array(value, &array);
    int exp = s21_get_exp(value);
    if (exp > 28) return 1;
    for (int j = 0; j < exp; j++) {
        for (int i = 0; i < 29; i++) array[i] = array[i+1];
        array[29] = 0;
    }
    s21_from_ten_array_to_decimal(&array, result);
    if (s21_get_bit(value, 127) == 1) {
        result->bits[0]++;
        result->bits[2] = 0;
        s21_set_bit_V2(result, 127, 1);
    }
    else result->bits[2] = 0;
    return 0;
}