#include"s21_decimal.h"

int main() {

  s21_decimal src1, src2, origin;
  // src1 = 12345677.987654345678987654346;
  //           12345677.987654345678987654346
  // src2 = 87654323456.987654567898765300000;
  //           12345677.987654345678987654346
                                            
  // 87654323456.9876545678987653
  // printf("\ns21_subTest19 s21_subTest19 s21_subTest19\n\n");

  src1.bits[0] = 0b10010001000010101111010011001010;
  src1.bits[1] = 0b11000000010001011101010111110010;
  src1.bits[2] = 0b00100111111001000001101100000000;
  src1.bits[3] = 0b00000000000101010000000000000000;

  src2.bits[0] = 0b00010001110011011101000110000101;
  src2.bits[1] = 0b11110101101111000110111111000000;
  src2.bits[2] = 0b00000010110101010000111100111111;
  src2.bits[3] = 0b00000000000100000000000000000000;

  printf("First decimal\n");
  s21_print_decimal(src1);

  printf("Second decimal\n");
  s21_print_decimal(src2);

  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);
  // 87641977779.00000022221977764 exp 17

  origin.bits[0] = 0b10010010000001100111100010100100;
  origin.bits[1] = 0b10001011011010100100100011011111;
  origin.bits[2] = 0b00011100010100011001001100010001;
  origin.bits[3] = 0b10000000000100010000000000000000;

  printf("First decimal\n");
  s21_print_decimal(src1);

  printf("Second decimal\n");
  s21_print_decimal(src2);

  printf("RESULT ADD\n");
  s21_print_decimal(result);

  //printf("RESULT INT %d\n", res_int);

  //printf("RETURN = %d\n", add);


return 0;
}