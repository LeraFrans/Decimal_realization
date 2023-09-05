#include"s21_decimal.h"

#define U_MAX_INT 4294967295

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {


//printf("EXP = %d/n", s21_get_exp(value_1));
    int error = 0;
    error = s21_owerflow_before_normalization_for_add(value_1, value_2);
    if (error != 0) return error;
    error = s21_check_exponenta(value_1, value_2);
    if (error != 0) return error;

    int res = 0;
    s21_decimal res_first = {0, 0, 0, 0};
    s21_decimal res_second = {0, 0, 0, 0};

    int remaind_1[30] = {0};
    int remaind_2[30] = {0};
    s21_normalization(value_1, value_2, &res_first, &res_second, remaind_1, remaind_2);
//printf("\n result decimals after normalization\n");
//s21_print_decimal(res_first);
//s21_print_decimal(res_second);
    
    //если оба положительные
    if (s21_get_bit(res_first, 127) == 0 && s21_get_bit(res_second, 127) == 0) {
        if (s21_sum_mantissa(res_first, res_second, result) == 3) res = 1;
        if (s21_banking_round_for_add(remaind_1, remaind_2, result) == 1) res = 1;
    }

    //если оба отрицательные
    else if (s21_get_bit(value_1, 127) == 1 && s21_get_bit(value_2, 127) == 1) {
        s21_set_bit_V2(&res_first, 127, 0);
        s21_set_bit_V2(&res_second, 127, 0);
        if (s21_sum_mantissa(res_first, res_second, result) == 3) res = 2;
        if (s21_banking_round_for_add(remaind_1, remaind_2, result) == 1) res = 2;
        s21_set_bit_V2(result, 127, 1);
    }

    //если только первое отрицательное
     else if (s21_get_bit(res_first, 127) == 1 && s21_get_bit(res_second, 127) == 0) {
        s21_set_bit_V2(&res_first, 127, 0);
        //первое по модулю больше
        if (s21_compare_mantissa(res_first, res_second) == 1) {
//printf("I TUT SUKA\n");
            if (s21_minus_positiv_mantissa(res_first, res_second, result) == 3) res = 2;
            if (s21_banking_round_for_sub(remaind_1, remaind_2, result) == 1) res = 2;
            s21_set_bit_V2(result, 127, 1);
        }
        //второе по модулю больше
        else if (s21_compare_mantissa(res_first, res_second) == 2) {
//printf("WHAT\n");
            if (s21_minus_positiv_mantissa(res_second, res_first, result) == 3) res = 1;
            if (s21_banking_round_for_sub(remaind_2, remaind_1, result) == 1) res = 1;
        }
        //else printf("KAVO\n");
    }

    //если только второе отрицательное
    else if (s21_get_bit(res_first, 127) == 0 && s21_get_bit(res_second, 127) == 1) {
        s21_set_bit_V2(&res_second, 127, 0);
        //второе больше по модулю
        if (s21_compare_mantissa(res_first, res_second) == 2) {
//printf("YYYYYY\n");
            if (s21_minus_positiv_mantissa(res_second, res_first, result) == 3) res = 2;
            if (s21_banking_round_for_sub(remaind_2, remaind_1, result) == 1) res = 2;
            s21_set_bit_V2(result, 127, 1);
        }
        //первое больше по модулю
        else if (s21_compare_mantissa(res_first, res_second) == 1) {
            if (s21_minus_positiv_mantissa(res_first, res_second, result) == 3) res = 1;
            if (s21_banking_round_for_sub(remaind_1, remaind_2, result) == 1) res = 1;
        }
    }
    //printf("\n result decimal after add\n");
    //s21_print_decimal(*result);

    return res;
}

//Проверяет, нет ли переполнения до того, как нормализация сведет к нулю маленькое число
//Возвращает 0 - если все хорошо, 1 - переполнение в сторону положительной бесконечности, 2 - переполнение в сторону отрицательной бесконечности
int s21_owerflow_before_normalization_for_add(s21_decimal value_1, s21_decimal value_2) {
    int res = 0;

    if (value_1.bits[0] == INFINITY || value_1.bits[1] == INFINITY || value_1.bits[2] == INFINITY) {
        if (s21_get_bit(value_1, 127) == 0) res = 1;
        else res = 2;
    }
    else if (value_2.bits[0] == INFINITY || value_2.bits[1] == INFINITY || value_2.bits[2] == INFINITY) {
        if (s21_get_bit(value_2, 127) == 0) res = 1;
        else res = 2;
    }

    if (value_1.bits[0] == U_MAX_INT && value_1.bits[1] == U_MAX_INT && value_1.bits[2] == U_MAX_INT
    && s21_is_zero(value_2) == 1
    && s21_get_bit(value_1, 127) == 0 && s21_get_bit(value_2, 127) == 0) res = 1;

    else if (value_2.bits[0] == U_MAX_INT && value_2.bits[1] == U_MAX_INT && value_2.bits[2] == U_MAX_INT
    && s21_is_zero(value_1) == 1
    && s21_get_bit(value_2, 127) == 0 && s21_get_bit(value_1, 127) == 0) res = 1;

    else if (value_1.bits[0] == U_MAX_INT && value_1.bits[1] == U_MAX_INT && value_1.bits[2] == U_MAX_INT
    && s21_is_zero(value_2) == 1
    && s21_get_bit(value_1, 127) == 1 && s21_get_bit(value_2, 127) == 1) res = 2;

    else if (value_2.bits[0] == U_MAX_INT && value_2.bits[1] == U_MAX_INT && value_2.bits[2] == U_MAX_INT
    && s21_is_zero(value_1) == 1
    && s21_get_bit(value_2, 127) == 1 && s21_get_bit(value_1, 127) == 1) res = 2;

    return res;
}


//Если экспонента больше 28 у положительного децимала, возвращается 1, если у отрицательного - 2, если экспоента корректна - 0
int s21_check_exponenta(s21_decimal value_1, s21_decimal value_2) {
    int res = 0;

    if ((s21_get_exp(value_1) > 28 && s21_get_bit(value_1, 127) == 0) || (s21_get_exp(value_2) > 28 && s21_get_bit(value_2, 127) == 0)) res = 1;
    else if ((s21_get_exp(value_1) > 28 && s21_get_bit(value_1, 127) == 1) || (s21_get_exp(value_2) > 28 && s21_get_bit(value_2, 127) == 1)) res = 2;

    return res;
}

//Для чисел, не вмещающихся в децимал. Производит банковское округление по последним цифрам. 
//Возвращает 1 в случае переполнения мантиссы, 0 - если все хорошо
int s21_banking_round_for_add (int remainder_1[], int remainder_2[], s21_decimal *result) {

    s21_sum_of_ten_array (remainder_1, remainder_2);
    //теперерь сумма двух массивов хранится в remainder_1


    int last_digit = 0;
    for (int i = 29; i <= 0; i--) {
        if (remainder_1[i] != 0) {
            last_digit = remainder_1[i];
            break;
        }
    }

    if (last_digit > 15) {
        if (result->bits[2] == U_MAX_INT && result->bits[1] == U_MAX_INT && result->bits[0] > U_MAX_INT-2) return 1;
        result->bits[0] += 2;
    }
    else if (last_digit == 15) {
        if (result->bits[0] % 2 == 0) {
            if (result->bits[2] == U_MAX_INT && result->bits[1] == U_MAX_INT && result->bits[0] > U_MAX_INT-2) return 1;
            result->bits[0] += 2;
        }
        else {
            if (result->bits[2] == U_MAX_INT && result->bits[1] == U_MAX_INT && result->bits[0] > U_MAX_INT-1) return 1;
            result->bits[0] += 1;
        }
    }
    else if (last_digit > 5) {
        if (result->bits[2] == U_MAX_INT && result->bits[1] == U_MAX_INT && result->bits[0] > U_MAX_INT-1) return 1;
        result->bits[0] += 1;
    }
    else if (last_digit == 5 && result->bits[0] % 2 == 1) {
            if (result->bits[2] == U_MAX_INT && result->bits[1] == U_MAX_INT && result->bits[0] > U_MAX_INT-1) return 1;
            result->bits[0] += 1;
    }
    return 0;
}


//Для чисел, не вмещающихся в децимал. Производит банковское округление по последним цифрам. 
//Возвращает 1 в случае переполнения мантиссы, 0 - если все хорошо
int s21_banking_round_for_sub (int remainder_1[], int remainder_2[], s21_decimal *result) {

    int flag_minus_one = 0;
    if (s21_compare_ten_array(remainder_1, remainder_2) == -1) {
        
        int position_in_array = 29;
        for (int i = 29; i >= 0; i--) {
            if (remainder_2[i] != 0) {
                //printf("i = %d\n", i);
                position_in_array = i+1;
                break;
            }
        }
        //printf("POSITION = %d\n", position_in_array);
        remainder_1[position_in_array] = 1;
        flag_minus_one = 1;
    }

    //print_ten_array(remainder_1);
    //print_ten_array(remainder_2);

    s21_sub_of_ten_array (remainder_1, remainder_2);
    //теперерь разность двух массивов хранится в remainder_1

    if (flag_minus_one == 1) result->bits[0]--;

    //print_ten_array(remainder_1);

    int last_digit = 0;
    for (int i = 29; i <= 0; i--) {
        if (remainder_1[i] != 0) {
            last_digit = remainder_1[i];
            break;
        }
    }


    if (last_digit > 5) {
        if (result->bits[2] == U_MAX_INT && result->bits[1] == U_MAX_INT && result->bits[0] > U_MAX_INT-1) return 1;
        result->bits[0] += 1;
    }
    else if (last_digit == 5 && result->bits[0] % 2 == 1) {
            if (result->bits[2] == U_MAX_INT && result->bits[1] == U_MAX_INT && result->bits[0] > U_MAX_INT-1) return 1;
            result->bits[0] += 1;
    }
    return 0;
}