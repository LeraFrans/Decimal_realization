#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<math.h>

typedef struct
{
    unsigned int bits[4];
} s21_decimal;

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


// для вызова необходимо создать массив интов и потом его очистить 
// int *array = calloc(30, sizeof(int));
// s21_decimal_to_ten_array(value, array);
//   ...работаем с ним...
// free(array);
void s21_from_decimal_to_ten_array(s21_decimal value, int result[]) {
    int* add = calloc(30, sizeof(int));
    add[0] = 1;
    for (int i = 0; i<96; i++) {
        if (s21_get_bit(value, i)) s21_sum_of_ten_array (result, add);
        s21_sum_of_ten_array (add, add);
    }
}

//Делит десятичный массив на 2. Изменяет сам массив по указателю, возвращает остаток от деления (либо 1, либо 0)
int s21_div_two_ten_array (int value[]) {
    //printf("HHHHHHHHHHH\n");
    //int res_remainder = 0;
    int res[30] = {0};
    int flag_start = 0;
    int remainder = 0, quotient = 0;
    for (int i = 29; i >= 0; i--) {
        if (flag_start == 0 && value[i] == 0) continue;
        else {
            flag_start = 1;
            quotient = value[i] + (remainder*10);
            res[i] = quotient/2;
            remainder = quotient%2;
        }
    }

    for (int i = 0; i < 29; i++) value[i] = res[i];
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
    s21_decimal copy_result = {0, 0, 0, 0};
    int i = 0;
    while (is_zero_array(array) != 1) {
        //printf("\n\nFINISH1\n\n");
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

void s21_print_decimal(s21_decimal value) {
    for (int i = 127; i >= 0; i--) {
        if((i + 1) % 32 == 0) printf("|");
        printf("%d ", s21_get_bit(value, i));
    }
    printf("\n");
    
}

int s21_get_exp(s21_decimal value) {
    int res = 0;
    value.bits[3] << 1;
    value.bits[3] >> 17;
    return value.bits[3];
}


// тут добавить случай, когда мантисса переполнилась и уже больше нельзя увеличивать её и экспоненту. Тогда начинаем двигать вторую 
// экспоненту вниз  
void s21_normalization (s21_decimal value_1, s21_decimal value_2, s21_decimal *result_1, s21_decimal *result_2) {

    // printf("\n\n\n");
    // s21_print_decimal(value_1);
    // printf("\n\n\n");

    int exp_1 = s21_get_exp(value_1);
    int exp_2 = s21_get_exp(value_2);
    int difference = exp_1 - exp_2;
    //printf("exp_1 = %d\n", exp_1);


    //если первая экспонента больше, значит работем со вторым децималом
    if (difference > 0) {
        for (int i = 0; i < difference; i++) {
            exp_2++;
             
            int array[30] = {0};
            s21_from_decimal_to_ten_array(value_2, array);
            //умножаем на 10
            
            for (int i = 30; i > 0; i--) array[i] = array[i-1];
            array[0] = 0;

            s21_from_ten_array_to_decimal(array, result_2);

            result_2->bits[3] = exp_2;

        }
        for (int i = 0; i < 4; i++) result_1->bits[i] = value_1.bits[i];
    }
    //если первая экспонента меньше, то работаем с ней
    else {
        difference = -difference;
        for (int i = 0; i < difference; i++) {
            exp_1++;
            
            int array[30] = {30};
            s21_from_decimal_to_ten_array(value_1, array);
            //умножаем на 10
            for (int i = 30; i > 0; i--) array[i] = array[i-1];
            array[0] = 0;
            s21_from_ten_array_to_decimal(array, result_1);
            result_1->bits[3] = exp_1;
            //free(array);
        }
        for (int i = 0; i < 4; i++) result_2->bits[i] = value_2.bits[i];
    }

}

//Мейьи сделать статику, ибо на фри крашится. Мб сложение сделать не через 
//нормлизацию, а через мою функцию сложения, просто сдвинуть индекс (вычитание так же)


int main() {
    
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
    s21_decimal m = {12345, 0, 0, 4};
    s21_decimal n = {67891, 0, 0, 1};
    printf("\nBefore normalization\n");
    printf("\nm: ");
    s21_print_decimal(m);
    printf("\nn: ");
    s21_print_decimal(n);


    s21_decimal res_m = {0, 0, 0, 0};
    s21_decimal res_n = {0, 0, 0, 0};

    s21_normalization(m, n, &res_m, &res_n);


    printf("\nAfter normalization\n");
    printf("\nm: ");
    s21_print_decimal(res_m);
    printf("\nn: ");
    s21_print_decimal(res_n);





//free(a);
//free(b);


    return 0;
}
