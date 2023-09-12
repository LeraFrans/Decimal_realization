#include "s21_decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int res = 0;

    //определяем знак результирующего децимала (0 - плюс, 1 - минус)
    int sign = 0;
    if ( (s21_get_bit(value_1, 127) == 1 && s21_get_bit(value_2, 127) == 0) || (s21_get_bit(value_1, 127) == 0 && s21_get_bit(value_2, 127) == 1)) sign = 1;

    //переводим всё в биг децималы и биг десятичные массивы
    s21_big_decimal big_value_1 = {0};
    s21_big_decimal big_value_2 = {0};
    s21_cpy_decimal_to_big_decimal(value_1, &big_value_1);
    s21_cpy_decimal_to_big_decimal(value_2, &big_value_2);
    s21_big_decimal big_result = {0}; 

    int big_ten_array_1 [90] = {0};
    int big_ten_array_2 [90] = {0};
    s21_from_big_decimal_to_ten_array(big_value_1, big_ten_array_1);
    s21_from_big_decimal_to_ten_array(big_value_2, big_ten_array_2);
    int big_ten_array_result [90] = {0};

    //нужно избавиться от экспонент и превратить оба числа в "целые"
    //для этого находим разность экспонент и столько раз домножаем число с меньшей экспонентой на 10
    //при этом обе экспоненты становятся равными нулю
    int exp_1 = s21_get_exp(value_1);
    int exp_2 = s21_get_exp(value_2);
    int diff_exp = exp_1 - exp_2;
    //у первой экспонента больше, поэтому двигаем вторую 
    if (diff_exp > 0) {
        for (int i = 0; i < diff_exp; i++) s21_mul_ten_big_ten_array(big_ten_array_2);
    }
    //у второй экспонента больше, значит двигаем первую
    else if (diff_exp < 0) {
        for (int i = 0; i < -diff_exp; i++) s21_mul_ten_big_ten_array(big_ten_array_1);
    }

    //непосредственно деление мантисс (алгоритм как у обычного деления в столбик)
    int exp_rezult = s21_div_big_ten_array(big_ten_array_1, big_ten_array_2, big_ten_array_result);

    


    



    return res;
}


//делит два больших десятичных массива, алгоритм похож на обычное деление в столбик ручками
//в качестве результата возвращает экспоненту результата
int s21_div_big_ten_array (int value_1[], int value_2[], int result[]) {
    
    int exp_result = 0;

    int counter = 0;  //индекс первого числа (самого старшеразрядного) в value_1, чтобы друг под другом разместить
    //далее это индекс той цифры в value_1, которую сносим вниз
    int a[90] = {0};  //уменьшаемое на каждом шаге
    int b[90] = {0};  //вычитаемое на каждом шаге
    int quotient = 0; //частное на каждом шаге
    int size_of_ab = 0; //количество значимых цифр при пошаговом вычитании

    //находим first_digit (индекс первого числа в массиве)
    for (int i = 89; i >= 0; i--) {
        if (value_1[i] != 0) {
            counter = i;
            break;
        }
    }

    //находим size_of_ab 
    for (int i = 89; i >= 0; i--) {
        if (value_2[i] != 0) {
            size_of_ab = i+1;
            break;
        }
    }

    //изначально b это и есть value_2
    for (int i = 0; i < 89; i++) b[i] = value_2[i];

    //определяем изначальное а (переписываем первые size_of_ab цифр из value_1)
    for (int i = 0; i < size_of_ab; i++) a[i]  = value_1[counter - size_of_ab + 1  + i];
    counter = counter - size_of_ab + 1;  //7 - 3 + 1 = 5

    //если а меньше b, то в а сносим ещё одну цифру
    if (s21_compare_big_ten_array(a, b) == -1) {
        //если дошли до конца и больше сносить нечего, то сносим 0, а результирующую экспоненту увеличивает на 1
        if (counter == 0) {
            s21_mul_ten_big_ten_array(a);
            exp_result++;
        }
        //если есть, что сносить, то сносим цифру под индексом counter-1, сам counter сдвигаем дальше
        else {
            s21_mul_ten_big_ten_array(a);
            counter--;
            a[0] = value_1[counter];
        }
        //size_of_ab++       это нужно сделать только один раз, хз как (и хз, надо ли вообще)
    }
    





    return exp_result;
}

//просто умножает большой десятичный массив на 10 (без обработки каких-либо ошибок)
void s21_mul_ten_big_ten_array (int value[]) {
    for (int j = 89; j > 0; j--) value[j] = value[j-1];
            value[0] = 0;
}