#include "s21_decimal.h"

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
    //s21_cpy_decimal_to_big_decimal(value_2, &big_value_2);

//printf("Big_value_1 in start\n");
//s21_print_big_decimal(big_value_1);
//printf("HERE value_2 in start = %d\n", value_2.bits[0]);
//s21_print_decimal(value_2);
//s21_print_big_decimal(big_value_2);

    s21_big_decimal big_result = {0}; 
//printf("start cpy_big_value_1.bits[4] = %d\n", cpy_big_value.bits[4]);
    for (int i = 0; i < 96; i++) {
        if (s21_get_bit(value_2, i) == 1) {
            //вот тут чтобы адекватно прыгало в следующий бит нужно сделать
            //big_value_1 << i;
            s21_big_decimal cpy_big_value_1 = {0};
//printf("FFFF after cpy value_1 to big = %d\n", cpy_big_value_1.bits[4]);
            for (int j = 223; j >= i; j--) {
                s21_set_bit_V2_for_big_decimal(&cpy_big_value_1, j, s21_get_bit_for_big_decimal(big_value_1, j - i));
            }
            //for (int k = 0; 0 < i; k++) s21_set_bit_V2_for_big_decimal(&big_result, k, 0);
//printf("GGGG after shift and before summ = %d\n", cpy_big_value_1.bits[4]);
//printf("CPY VALUE 1. SHIFT I = %d\n", i);


//     ЕБУЧАЯ МАГИЯ НАЧАЛАСЬ)

//s21_print_big_decimal(cpy_big_value_1);

            s21_sum_mantisa_for_big_decimal(&big_result, cpy_big_value_1);
//printf("%d after summ big_result.bits[4] = %d\n", i, big_result.bits[4]);
        }
    }
//Вот эта хуита не отрабaтывает (уже вроде как работает))
    int big_ten_array[90] = {0};
    s21_from_big_decimal_to_ten_array(big_result, big_ten_array);


printf("Create big_ten_array\n");
s21_print_big_ten_array(big_ten_array);



//printf("WORKING");
// До этого момента работает


    int exp_1 = s21_get_exp(value_1);
    int exp_2 = s21_get_exp(value_2);
    int res_exp = abs(exp_1 + exp_2);
    int sign = exp_1 + exp_2 >= 0 ? 0 : 1;
    if (res_exp > 28) {
        int diff = res_exp - 28;
        int remainder = 0;
        for (int i = 0; i < diff; i++) {
            res_exp --;
            remainder = big_ten_array[0];
            for (int j = 0; j < 89; j++) big_ten_array[i] = big_ten_array[i+1];
            big_ten_array[89] = 0;
        }
    }

printf("After shift\n");
s21_print_big_ten_array(big_ten_array);


    int flag_owerflow_mantisa = 0;
    //нужно проверить, вмещается ли целая часть в мантиссу (сравнить с максимальным беззнаковым инт децимала в рамках десятичного массива),
    // остальное (цифры после запятой) при переводе в обычный децимал можно отбросить, применив банковское округление
    int max_ten_array[] = {5, 3, 3, 0, 5, 9, 3, 4, 5, 3, 9, 5, 7, 3, 3, 4, 6, 2, 4, 1, 5, 2, 6, 1, 8, 2, 2, 9, 7, 0};
    int mantisa_ten_array[90] = {0};
    int counter = 0;
    for (int i = res_exp; i < 90; i++) {
        mantisa_ten_array[counter] = big_ten_array[i];
        if (counter >= 28 && big_ten_array[i] != 0) {
            flag_owerflow_mantisa = 1;
            break;
        }
        counter++;
    } 
    if (s21_compare_ten_array(mantisa_ten_array, max_ten_array) == 1) flag_owerflow_mantisa = 1;

//printf("FINAL MANTISA\n");
//s21_print_big_ten_array(mantisa_ten_array);
    

    return res;
}

//результат хранится в value_1;
void s21_sum_mantisa_for_big_decimal (s21_big_decimal *value_1, s21_big_decimal value_2) {
    int next = 0;
    int sign_next = 0;
    int bit_1 = 0, bit_2 = 0;

    s21_decimal result = {0};

    for (int i = 0; i < 224; i++) {
        bit_1 = s21_get_bit_for_big_decimal(*value_1, i);
        bit_2 = s21_get_bit_for_big_decimal(value_2, i);
        next += bit_1 + bit_2;
        result.bits[i / 32] |= ((next % 2) << (i % 32));
        if(next == 1) next = 0;
        if(next > 1) next = 1;
    }

    for (int i = 0; i < 8; i++) value_1->bits[i] = result.bits[i];
}

void s21_print_big_decimal(s21_big_decimal value) {
    for (int i = 0; i < 256; i++) {
        if (i % 32 == 0) printf("\n");
        printf("%d ", s21_get_bit_for_big_decimal(value, i));
    }
    printf("\n");
}

void s21_print_big_ten_array(int value[]) {
    printf("Big ten array:\n");
    for (int i = 0; i < 90; i++) printf("%d ", value[i]);
    printf("\n");
}

void s21_from_big_decimal_to_ten_array(s21_big_decimal value, int result[]) {
    int add[90] = {0};
    add[0] = 1;
    for (int i = 0; i<224; i++) {
        if (s21_get_bit_for_big_decimal(value, i)) {
            s21_sum_of_ten_array_for_big_decimal (result, add);
            //printf("SUM in I = %d is:\n", i);
            //s21_print_big_ten_array(result);
        }
        s21_sum_of_ten_array_for_big_decimal (add, add);
    }
}

void s21_sum_of_ten_array_for_big_decimal (int value_1[], int value_2[]) {
    int remainder = 0;

    //s21_print_big_ten_array(value_1);
    //printf("HHHHHHHHHHH%dHHHHHHHHHHH\n", value_1[50]);
    for (int i = 0; i < 90; i++) {
        int res = value_1[i] + value_2[i] + remainder;
        value_1[i] = res%10;
        //printf("value_1[%d] = %d\n", i, value_1);
        remainder = res/10;
    }
    //Тут нужно проверить на переполнение и вернуть ошибку если что
}

int is_zero_array_for_big_decimal (int array[]) {
    int res = 1;
    for (int i = 0; i < 90; i++) {
        if (array[i] != 0) {
            res = 0;
            break;
        }
    }
    //if (res == 1) printf("\n\nSSSSSSSSSSSSSSSSSSS\n\n");
    return res;
}

int s21_set_bit_V2_for_big_decimal(s21_big_decimal *result, int position, int value) { //0 - OK, 1 - ERROR, position 0-127
    int res = 0;
    if((result != NULL) && (position > -1 && position < 256) && (value == 0 || value == 1)) {
        int byte = position / 32;
        int bit = position % 32;
        if (value == 1) result->bits[byte] |= (1 << bit);
        else result->bits[byte] &= ~(1 << bit);
    } else res = 1;
    return res;
}

void s21_from_ten_array_to_big_decimal(int array[], s21_big_decimal *result) {
    s21_big_decimal copy_result = {0};
    int i = 0;
//int max_array[] = {5, 3, 3, 0, 5, 9, 3, 4, 5, 3, 9, 5, 7, 3, 3, 4, 6, 2, 4, 1, 5, 2, 6, 1, 8, 2, 2, 9, 7, 0};
    while (is_zero_array_for_big_decimal(array) != 1 ) {
        s21_set_bit_V2_for_big_decimal(&copy_result, i, s21_div_two_ten_array_for_big_decimal(array));
        i++;
    }
    
    for (int i = 0; i < 96; i++) {
        s21_set_bit_V2_for_big_decimal(result, i, s21_get_bit_for_big_decimal(copy_result, i));
    }
}

int s21_div_two_ten_array_for_big_decimal (int value[]) {
    int res[90] = {0};
    int flag_start = 0;
    int remainder = 0, quotient = 0;
    for (int i = 89; i >= 0; i--) {
        if (flag_start == 0 && value[i] == 0) continue;
        else {
            flag_start = 1;
            quotient = value[i] + (remainder*10);
            res[i] = quotient/2;
            remainder = quotient%2;
        }
    }

    for (int i = 0; i <= 89; i++) value[i] = res[i];

    return remainder;
}

int s21_get_bit_for_big_decimal(s21_big_decimal value, int position) {  // -1 - ERROR, position 0-127
    int res = -1;
    if((position > -1 && position < 256)) {

        int byte = position / 32;
        int bit = position % 32;
        //printf("byte: %d bit: %d ", byte, bit);
        res = value.bits[byte] & (1 << bit);
        if(res != 0) res = 1;
    }
    return res;
}

