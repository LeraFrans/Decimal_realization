#ifndef _S21_DECIMAL_H_
#define _S21_DECIMAL_H_

#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<math.h>
#include<string.h>

typedef struct
{
    unsigned int bits[4];
} s21_decimal;

typedef struct
{
    unsigned int bits[8];
} s21_big_decimal;

#define SIGN_BIT 0x80000000
#define OK 0
#define NULL_POINTER_EXEPTION 1
#define EXPONENT_EXEPTION 2
#define S21_OVERFLOW 3

#define S21_MAX_UINT 4294967295
#define EXPONENT_MINUS_1 2147549184   // 0b10000000000000010000000000000000
#define EXPONENT_PLUS_1 65536         // 0b00000000000000010000000000000000
#define EXPONENT_PLUS_2 196608        // 0b00000000000000110000000000000000
#define EXPONENT_MINUS_28 2149318656  // 0b10000000000111000000000000000000
#define EXPONENT_PLUS_28 1835008      // 0b00000000000111000000000000000000

//help(me please)
int s21_set_bit(s21_decimal value, s21_decimal *result, int position);
int s21_get_bit(s21_decimal value, int position);
int s21_invert_bit(s21_decimal value, s21_decimal *result, int position);
int s21_get_last_bit(s21_decimal value);
int s21_is_correct_decimal(s21_decimal value);
int s21_get_exp(s21_decimal value);
int s21_set_exp(s21_decimal value, s21_decimal *result, int exp);
void s21_cpy_decimal(s21_decimal src, s21_decimal* dest);
int s21_init_zero_decimal(s21_decimal *value);  //0 - OK, 1 - ERROR 
int s21_cpy_decimal_to_big_decimal(s21_decimal src, s21_big_decimal *dst);
int s21_is_zero(s21_decimal value);
void s21_print_decimal(s21_decimal value);

void print_ten_array(int array[]);
int s21_eq_ten_array (int value_1[], int value_2[]);
void s21_sum_of_ten_array (int value_1[], int value_2[]);
int s21_sub_of_ten_array (int value_1[], int value_2[]);
void s21_from_decimal_to_ten_array(s21_decimal value, int result[]);
int s21_div_two_ten_array (int value[]);
int is_zero_array (int array[]);
int s21_set_bit_V2(s21_decimal *result, int position, int value);
void s21_from_ten_array_to_decimal(int array[], s21_decimal *result);
int s21_compare_ten_array (int array_1[], int array_2[]);
void s21_normalization (s21_decimal value_1, s21_decimal value_2, s21_decimal *result_1, s21_decimal *result_2, int remaind_1[], int remaind_2[]);
int s21_owerflow_before_normalization_for_add(s21_decimal value_1, s21_decimal value_2);
int s21_check_exponenta(s21_decimal value_1, s21_decimal value_2);
int s21_banking_round_for_add (int remainder_1[], int remainder_2[], s21_decimal *result);
int s21_banking_round_for_sub (int remainder_1[], int remainder_2[], s21_decimal *result);
int is_zero_array_for_big_decimal (int array[]);


//for big decimal
void s21_banking_round_for_mult(int big_ten_array[], int remainder);
int s21_compare_big_ten_array (int array_1[], int array_2[]);
void s21_print_big_decimal(s21_big_decimal value);
void s21_print_big_ten_array(int value[]);
void s21_from_big_decimal_to_ten_array(s21_big_decimal value, int result[]);
void s21_sum_mantisa_for_big_decimal (s21_big_decimal *value_1, s21_big_decimal value_2);
void s21_print_big_decimal(s21_big_decimal value);
void s21_sum_of_ten_array_for_big_decimal (int value_1[], int value_2[]);
int s21_set_bit_V2_for_big_decimal(s21_big_decimal *result, int position, int value);
void s21_from_ten_array_to_big_decimal(int array[], s21_big_decimal *result);
int s21_div_two_ten_array_for_big_decimal (int value[]);
int s21_get_bit_for_big_decimal(s21_big_decimal value, int position);


//arithmetic
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sum_mantissa(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);    //0 - OK, 1 - NULL pointer, 2 - wrong exp, 3 - overflow mantissa
//int s21_badd(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
//int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_bmul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_minus_positiv_mantissa(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
void s21_div_two(s21_decimal *value);
int s21_mul_two(s21_decimal *value);
int s21_mul_two_pow(s21_decimal *value, int pow);
int s21_div_by_ten(s21_decimal value, s21_decimal *result);
int s21_mul_ten_mantissa(s21_decimal value, s21_decimal *result);
int s21_increase_exp(s21_decimal value, s21_decimal* result);
int s21_decrease_exp(s21_decimal value, s21_decimal* result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);


//convertors
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);


int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result); // 0 - OK, 1 - ERROR

//compare
int s21_is_equal(s21_decimal, s21_decimal);
int s21_compare_mantissa(s21_decimal value_1, s21_decimal value_2);




#endif
