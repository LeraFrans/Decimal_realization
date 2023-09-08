#include"s21_decimal.h"

int main() {

  int num1 = 9403;
  int num2 = 202;
  int res_origin = 1899406;

  s21_decimal a = {num1, 0, 0, 0};
  s21_decimal b = {num2, 0, 0, 0};

  s21_decimal result = {0};

  int mul = s21_mul(a, b, &result);

  // int a[90] = {0};
  // a[0] = 9;
  // a[1] = 1;
  // int b[90] = {0};
  // b[0] = 0;
  // b[1] = 9;
  // b[2] = 1;

  // s21_sum_of_ten_array_for_big_decimal(a, b);

  // s21_print_big_ten_array(a);

  

  // printf("First decimal\n");
  // s21_print_decimal(src1);

  // printf("Second decimal\n");
  // s21_print_decimal(src2);

  // printf("RESULT ADD\n");
  // s21_print_decimal(result);

  //printf("RESULT INT %d\n", res_int);

  //printf("RETURN = %d\n", add);


return 0;
}