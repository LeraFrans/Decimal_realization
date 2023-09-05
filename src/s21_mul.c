#include "s21_decimal.c"

// Умножение двух децималов
//Функции возвращают код ошибки:
//0 - OK
//1 - число слишком велико или равно бесконечности
//2 - число слишком мало или равно отрицательной бесконечности
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int res = 0;

    s21_big_decimal big_value_1 = {0};
    s21_big_decimal big_value_2 = {0};
    s21_cpy_decimal_to_big_decimal(value_1, &big_value_1);
    s21_cpy_decimal_to_big_decomal(value_2, &big_value_2);

    s21_big_decimal big_result = {0}; 

    for (int i = 0; i < 96; i++) {
        if (s21_get_bit(value_2, i) == 1) {
            big_value_1 << i;
            s21_sum_mantisa_for_big_decimal(&big_result, big_value_1);
        }
    }

    int res_exp = s21_get_exp(value_1) + s21_get_exp(value_2);
    if (res_exp > 28) {
        int diff = res_exp - 28;
        for (int i = 0; i < diff; i++) {
            res_exp --;
            for (int j = 0; j < 29; j++) array_2[i] = array_2[i+1];
            array_2[29] = 0;
        }
    }

    

    return res;
}

//результат хранится в value_1;
void s21_sum_mantisa_for_big_decimal (s21_big_decimal *value_1, s21_big_deceimal value_2) {
    int next = 0;
    int sign_next = 0;
    int bit_1 = 0, bit_2 = 0;
//if(s21_init_zero_decimal(result) != 0) return NULL_POINTER_EXEPTION;    //result is NULL
//if(s21_set_exp(*result, result, s21_get_exp(value_1)) != 0) return EXPONENT_EXEPTION;  //wrong exp
    //test
    
//if(s21_get_bit(value_1, 127) == 1) s21_get_additional_code(value_1, &value_1);
//if(s21_get_bit(value_2, 127) == 1) s21_get_additional_code(value_2, &value_2);
    //printf("additional b:\n");
    //s21_print_decimal(value_2);
    //end
    for (int i = 0; i < 224; i++) {
        bit_1 = s21_get_bit(value_1, i);
        bit_2 = s21_get_bit(value_2, i);
        next += bit_1 + bit_2;
        result->bits[i / 32] |= ((next % 2) << (i % 32));
        if(next == 1) next = 0;
        if(next > 1) next = 1;

        
    }
    //test for additional code
//sign_next = s21_get_bit(value_1, 127) + s21_get_bit(value_2, 127) + next;
//if(sign_next % 2 == 1) s21_set_bit(*result, result, 127);

//if(sign_next > 1) sign_next = 1;
//else sign_next = 0;

//if(next != sign_next) return S21_OVERFLOW;
    //end
    //if(next != 0) return OVERFLOW; //overflow mantissa
//result->bits[3] = value_1.bits[3];
    return OK;
}

void s21_print_big_decimal(s21_big_decimal value) {
    ;
}