#include"s21_decimal.h"

void print_ten_array(int array[]) {
    printf("Ten array\n[ ");
    for (int i = 0; i < 30; i++) {
        printf("%d", array[i]);
    }
    printf(" ]\n");
}

// Сравнивает десятичные массивы. Возвращает: 1 если первое больше, -1 если первое меньше, 0 если равны
int s21_eq_ten_array (int value_1[], int value_2[]) {
    int res = 0;
    for (int i = 29; i <= 0; i--) {
        if (value_1[i] > value_2[i]) {
            res = 1;
            break;
        }
        if (value_1[i] < value_2[i]) {
            res = -1;
            break;
        }
    }
    return res;
}


// Cкладывает два десятичных массива, результат сохраняется в value_1
void s21_sum_of_ten_array (int value_1[], int value_2[]) {
    int remainder = 0;
    for (int i = 0; i<30; i++) {
        int res = value_1[i] + value_2[i] + remainder;
        value_1[i] = res%10;
        remainder = res/10;
    }
    //Тут нужно проверить на переполнение и вернуть ошибку если что
}

//Вычитает десятичные массивы (из value_1 вычитается value_2), результат сохраняется в value_1

//   Нужно проверить, какое число больше, а какое меньше и добавить эту обработку
// Для этого нужно написать функцию сравнения (либо сравнивать десятичне массивы, либо децималы)
// Плюс добавить обработку минусовых значений (подумать как передавать минусовые значения и нужно ли вообще это здесь)
int s21_sub_of_ten_array (int value_1[], int value_2[]) {
    //Тут нужно проверить, какое из чисел больше
    int error = 0;
    for (int i = 0; i < 30; i++) {
        if (value_1[i] < value_2[i]) {
            value_1[i] += 10;
            if (i != 29 )value_1[i+1] --;
            else error = 1;
        }
        value_1[i] -= value_2[i];
    }
    return error;
}

/*
int s21_get_bit(s21_decimal value, int position) {  // -1 - ERROR, position 0-127
    int res = -1;
    if((position > -1 && position < 128)) {

        int byte = position / 32;
        int bit = position % 32;
        //printf("byte: %d bit: %d ", byte, bit);
        res = value.bits[byte] & (1 << bit);
        if(res != 0) res = 1;
    }
    return res;
}
*/

// для вызова необходимо создать массив интов и потом его очистить 
// int *array = calloc(30, sizeof(int));
// s21_decimal_to_ten_array(value, array);
//   ...работаем с ним...
// free(array);
void s21_from_decimal_to_ten_array(s21_decimal value, int result[]) {
    int add[30] = {0};
    add[0] = 1;
    for (int i = 0; i<96; i++) {
        if (s21_get_bit(value, i)) s21_sum_of_ten_array (result, add);
        s21_sum_of_ten_array (add, add);
    }
}

//Делит десятичный массив на 2. Изменяет сам массив по указателю, возвращает остаток от деления (либо 1, либо 0)
int s21_div_two_ten_array (int value[]) {
    int res[30] = {0};
    int flag_start = 0;
    int remainder = 0, quotient = 0;
    for (int i = 29; i >= 0; i--) {
        if (flag_start == 0 && value[i] == 0) continue;
        else {
            flag_start = 1;
            quotient = value[i] + (remainder*10);
            //printf("quotient %d = %d\n", i, quotient);
            res[i] = quotient/2;
            //printf("res[%d] = %d\n", i, res[i]);
            remainder = quotient%2;
        }
    }

    for (int i = 0; i <= 29; i++) value[i] = res[i];
    //free(res);

    return remainder;
}


//Проверяет, состоит ли десятичный массив только из нулей (если да, то возвращает 1)
int is_zero_array (int array[]) {
    int res = 1;
    for (int i = 0; i < 30; i++) {
        if (array[i] != 0) {
            res = 0;
            break;
        }
    }
    //if (res == 1) printf("\n\nSSSSSSSSSSSSSSSSSSS\n\n");
    return res;
}



//В децимал result устанавливает на позицию position нужные бит value (1 или 0)
int s21_set_bit_V2(s21_decimal *result, int position, int value) { //0 - OK, 1 - ERROR, position 0-127
    int res = 0;
    if((result != NULL) && (position > -1 && position < 128) && (value == 0 || value == 1)) {
        int byte = position / 32;
        int bit = position % 32;
        if (value == 1) result->bits[byte] |= (1 << bit);
        else result->bits[byte] &= ~(1 << bit);
    } else res = 1;
    return res;
}

void s21_from_ten_array_to_decimal(int array[], s21_decimal *result) {
    s21_decimal copy_result = {0};
    int i = 0;
//int max_array[] = {5, 3, 3, 0, 5, 9, 3, 4, 5, 3, 9, 5, 7, 3, 3, 4, 6, 2, 4, 1, 5, 2, 6, 1, 8, 2, 2, 9, 7, 0};
    while (is_zero_array(array) != 1 ) {
        //printf("\n\nFINISH1\n\n");
        //print_ten_array(array);
        s21_set_bit_V2(&copy_result, i, s21_div_two_ten_array(array));
        //for (int i = 0; i < 30; i++) printf("%d", array[i]);
        //printf("\n");
        i++;
    }
    
    for (int i = 0; i < 96; i++) {
        s21_set_bit_V2(result, i, s21_get_bit(copy_result, i));
    }
    //printf("\n\nJJJJJJJJJJJJJJJ\n\n");
}

/*
void s21_print_decimal(s21_decimal value) {
    for (int i = 127; i >= 0; i--) {
        if((i + 1) % 32 == 0) printf("|\n");
        printf("%d ", s21_get_bit(value, i));
    }
    printf("\n");
    
}
*/

// int s21_get_exp(s21_decimal value) {
//     return (value.bits[3] << 1)>>17;
// }

//Сравнивает два десятичных массива, если первое больше, то возвращае т 1, если второе больше - -1, если равны - 0
int s21_compare_ten_array (int array_1[], int array_2[]) {
    int res = 0;
    for (int i = 29; i >= 0; i--) {
        if (array_1[i] > array_2[i]) {
            res = 1;
            break;
        }
        else if (array_2[i] > array_1[i]) {
            res = -1;
            break;
        }
    }
    return res;
}

/*
void s21_cpy_decimal(s21_decimal src, s21_decimal* dest) {
    for (int i = 0; i < 4; i++)
        dest->bits[i] = src.bits[i];
}
*/



// тут добавить случай, когда мантисса переполнилась и уже больше нельзя увеличивать её и экспоненту. Но за переполнением нужно в двоичке следить, а не в десятичке
//Тогда начинаем двигать вторую экспоненту вниз 
//Можно изначально проверить количество возможных смещений 
void s21_normalization (s21_decimal value_1, s21_decimal value_2, s21_decimal *result_1, s21_decimal *result_2, int remaind_1[], int remaind_2[]) {

    int flag_owerflow_mantisa = 0;
    int exp_1 = s21_get_exp(value_1);
    int exp_2 = s21_get_exp(value_2);
    int negative_value_1 =  s21_get_bit(value_1, 127);
    int negative_value_2 =  s21_get_bit(value_2, 127);
    int difference = exp_1 - exp_2;
    int max_array[] = {5, 3, 3, 0, 5, 9, 3, 4, 5, 3, 9, 5, 7, 3, 3, 4, 6, 2, 4, 1, 5, 2, 6, 1, 8, 2, 2, 9, 7, 0};

    //если первая экспонента больше, значит работем со вторым децималом
    if (difference > 0) {
        int array_2[30] = {0};
        s21_from_decimal_to_ten_array(value_2, array_2);
        //проверяем, не оверфловный ли массив у нас изначально
//printf("array_2 before\n");
//print_ten_array(array_2);
        //if (s21_compare_ten_array(array_2, max_array) == 1 || s21_compare_ten_array(array_2, max_array) == 0) flag_owerflow_mantisa = 1;
        for (int i = 0; i < difference && flag_owerflow_mantisa == 0; i++) {
            exp_2++;
            //умножаем на 10 один раз
            for (int i = 29; i > 0; i--) array_2[i] = array_2[i-1];
            array_2[0] = 0;
//printf("exp_2 = %d\n", exp_2);
//print_ten_array(array_2);
//printf("EXP = %d\n", exp_2);
            //делаем проверку на переполнение, сравнивая с максимальным массивом, если переполнено, возвращаемся обратно на один шаг и включаем флаг переполнения
//printf("owerflow = %d\n", owerflow);
            if (s21_compare_ten_array(array_2, max_array) == 1) {
//printf("\n\nOWERFLOW\n\n");
                flag_owerflow_mantisa = 1;
                exp_2--;
                for (int i = 0; i < 29; i++) array_2[i] = array_2[i+1];
                array_2[29] = 0;
                break;
            }
        };
        s21_from_ten_array_to_decimal(array_2, result_2);
        //если переполнено то работаем с первым децималом, первые мантиссу и экспонету уменьшаем до уровня вторых 
        if (flag_owerflow_mantisa == 1) {
            int array_1[30] = {0};
            s21_from_decimal_to_ten_array(value_1, array_1);
//printf("Array_1 before\n");
//print_ten_array(array_1);
            difference = exp_1 - exp_2;
            for (int i = 0; i < difference; i++) {
                exp_1--;
                remaind_1[i] = array_1[0];
                for (int i = 0; i < 29; i++) array_1[i] = array_1[i+1];
                array_1[29] = 0;
//print_ten_array(array_1);
            }
            s21_from_ten_array_to_decimal(array_1, result_1);
        }
        else {
            //просто скопировать первый децимал в результирующий, если мы его не трогали 
            s21_cpy_decimal(value_1, result_1);
        }
        s21_set_exp(*result_2, result_2, exp_2);
        s21_set_exp(*result_1, result_1, exp_1);
        //result_2->bits[3] = exp_2;r
        //result_1->bits[3] = exp_1;
        s21_set_bit_V2(result_1, 127, negative_value_1);
        s21_set_bit_V2(result_2, 127, negative_value_2);
    }



else if (difference < 0) {
    difference = -difference;
        int array_1[30] = {0};
        s21_from_decimal_to_ten_array(value_1, array_1);
        //проверяем, не оверфловный ли массив у нас изначально
//printf("array_1 before\n");
//print_ten_array(array_1);
        //if (s21_compare_ten_array(array_1, max_array) == 1 || s21_compare_ten_array(array_1, max_array) == 0) flag_owerflow_mantisa = 1;
        for (int i = 0; i < difference && flag_owerflow_mantisa == 0; i++) {
            exp_1++;
            //умножаем на 10 один раз
            for (int i = 29; i > 0; i--) array_1[i] = array_1[i-1];
            array_1[0] = 0;
//printf("exp_1 = %d\n", exp_1);
//print_ten_array(array_1);
            //делаем проверку на переполнение, сравнивая с максимальным массивом, если переполнено, возвращаемся обратно на один шаг и включаем флаг переполнения
//printf("owerflow = %d\n", owerflow);
            if (s21_compare_ten_array(array_1, max_array) == 1) {
//printf("\n\nOWERFLOW\n\n");
                flag_owerflow_mantisa = 1;
                exp_1--;
                for (int i = 0; i < 29; i++) array_1[i] = array_1[i+1];
                array_1[29] = 0;
                break;
            }
        }
//printf("exp_1 = %d\n NOWWWWWWWW\n", exp_1);
//print_ten_array(array_1);
        s21_from_ten_array_to_decimal(array_1, result_1);
        //если переполнено то работаем со вторым децималом, вторые мантиссу и экспонету уменьшаем до уровня вторых 
        if (flag_owerflow_mantisa == 1) {
            int array_2[30] = {0};
            s21_from_decimal_to_ten_array(value_2, array_2);
//printf("Array_2 before\n");
//print_ten_array(array_2);
            difference = exp_2 - exp_1;
//printf("DIFFERENCE = %d\n", difference);
            for (int i = 0; i < difference; i++) {
                exp_2--;
                remaind_2[i] = array_2[0];
                for (int i = 0; i < 29; i++) array_2[i] = array_2[i+1];
                array_2[29] = 0;
//print_ten_array(array_2);
            }
            s21_from_ten_array_to_decimal(array_2, result_2);
        }
        else {
            //просто скопировать второй децимал в результирующий, если мы его не трогали 
            //printf("\n\n\nJJJJJJJJ\n\n");
            s21_cpy_decimal(value_2, result_2);
        }

        s21_set_exp(*result_2, result_2, exp_2);
        s21_set_exp(*result_1, result_1, exp_1);
        // result_2->bits[3] = exp_2;
        // result_1->bits[3] = exp_1;
        s21_set_bit_V2(result_1, 127, negative_value_1);
        s21_set_bit_V2(result_2, 127, negative_value_2);
    }
    else {
        s21_cpy_decimal(value_1, result_1);
        s21_cpy_decimal(value_2, result_2);
    }

}

//Мейби сделать статику, ибо на фри крашится. Мб сложение сделать не через 
//нормлизацию, а через мою функцию сложения, просто сдвинуть индекс (вычитание так же)


//int main() {
    
    // int a[30] = {0};
    //  a[0] = 5;
    //  a[1] = 4;
    //  a[2] = 3;
    //  a[3] = 2;
    //  a[4] = 1;
    //s21_decimal example = {4294967295, 4294967295, 4294967295, 0};
    //s21_decimal example = {0, 0, 0, 0};
    // bits[0] = 101111000110000101001110
    // int b[30] = {0};
    // b[0] = 8;
    // b[1] = 7;
    // b[2] = 6;
    // b[3] = 5;
    //s21_from_decimal_to_ten_array(example, a);
    //int remainder = s21_div_two_ten_array(a);
    // s21_sum_of_ten_array(a, b);
    // printf("Array: ");
    // for (int i = 0; i<30; i++) printf("%d", a[i]);

    // s21_from_ten_array_to_decimal(a, &example);
    // printf("\nDecimal: ");
    // s21_print_decimal(example);
    //printf("/n Remainder = %d", remainder);

    // s21_from_decimal_to_ten_array(example, a);
    // printf("Array final: ");
    // for (int i = 0; i<30; i++) printf("%d", a[i]);
//    s21_decimal first = {12345, 0, 4294967, 0b10000000000000101000000000000000};
//    printf("exp 1 = %d\n", s21_get_exp(first));
//    s21_decimal second = {4294967293, 4294967295, 4294967, 0b00000000000000001000000000000000};

    //s21_decimal first = {12345, 0, 4294967, 8};
    //s21_decimal second = {4294967293, 4294967295, 0, 1};

//    printf("\nBefore normalization\n");
//    printf("\nfirst: ");
//    s21_print_decimal(first);
//    printf("\nsecond: ");
//    s21_print_decimal(second);


//    s21_decimal res_first = {0, 0, 0, 0};
//    s21_decimal res_second = {0, 0, 0, 0};

//    s21_normalization(first, second, &res_first, &res_second);
    //s21_normalization(second, first, &res_second, &res_first);

//    printf("\nAfter normalization\n");
//    printf("\nfirst: ");
//    s21_print_decimal(res_first);
//    printf("\nsecond: ");
//    s21_print_decimal(res_second);





//free(a);
//free(b);


//    return 0;
//}
