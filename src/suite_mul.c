#include "tests_suitcases.h"

START_TEST(mul_test_1) {
  int num1 = -10;
  int num2 = -10;
  int prod_int = 100;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_mul(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, prod_int);
}
END_TEST

START_TEST(mul_test_2) {
  int num1 = 10;
  int num2 = 20;
  int prod_int = 200;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_mul(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, prod_int);
}
END_TEST

START_TEST(mul_test_3) {
  int num1 = -10;
  int num2 = 20;
  int prod_int = -200;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_mul(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, prod_int);
}
END_TEST

START_TEST(mul_test_4) {
  int num1 = 9403;
  int num2 = 202;
  int res_origin = 1899406;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_mul(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(mul_test_5) {
  int num1 = -32768;
  int num2 = 2;
  int res_origin = -65536;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_mul(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(mul_test_6) {
  int num1 = -32768;
  int num2 = 32768;
  int res_origin = -1073741824;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_mul(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

// START_TEST(mul_test_7) {
//   float num1 = 9403.0e2;
//   int num2 = 202;
//   float res_origin = 1.899406e+08;                //189940600;
//   s21_decimal a = {0};
//   s21_decimal b = {0};
//   s21_from_float_to_decimal(num1, &a);
//   s21_from_int_to_decimal(num2, &b);
//   s21_decimal res_dec = {0};
//   float res_float = 0;
//   s21_mul(a, b, &res_dec);
//   s21_from_decimal_to_float(res_dec, &res_float);
//   ck_assert_float_eq(res_float, res_origin);
// }
// END_TEST

START_TEST(mul_test_8) {
  float num1 = 9403.0e2;
  float num2 = 9403.0e2;
  float res_origin = 884164090000;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_float_to_decimal(num1, &a);
  s21_from_float_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  float res_float = 0;
  s21_mul(a, b, &res_dec);
  s21_from_decimal_to_float(res_dec, &res_float);
  ck_assert_float_eq(res_float, res_origin);
}
END_TEST

START_TEST(s21_mul_1) {
  s21_decimal dec1 = {{4, 0, 0, 0}};
  s21_decimal dec2 = {{10, 0, 0, 0}};

  s21_decimal d22;
  s21_mul(dec1, dec2, &d22);

  int qqqq = 0;
  s21_from_decimal_to_int(d22, &qqqq);
  ck_assert_int_eq(qqqq, 40);
}
END_TEST

START_TEST(s21_mul_big_1) {
  s21_decimal dst1;
  dst1.bits[0] = 0b01110000000000000000000000000000;
  dst1.bits[1] = 0b10110011000000110001000010100111;
  dst1.bits[2] = 0b11100010001011101010010010010011;
  dst1.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal dst2;
  dst2.bits[0] = 0b00000000000000000000000000000001;
  dst2.bits[1] = 0b10000000000000100000000000000000;
  dst2.bits[2] = 0b00000000000000000000000000000000;
  dst2.bits[3] = 0b00000000000000000000000000000000;

  s21_decimal d22;
  int error = s21_mul(dst1, dst2, &d22);

  // int qqqq = 0;
  // s21_from_decimal_to_int(d22, &qqqq);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(s21_mul_big_2) {
  s21_decimal dst1;
  dst1.bits[0] = 0b01110000000000000000000000000000;
  dst1.bits[1] = 0b10110011000000110001000010100111;
  dst1.bits[2] = 0b11100010001011101010010010010011;
  dst1.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal dst2;
  dst2.bits[0] = 0b00000000000000000000000000000001;
  dst2.bits[1] = 0b10000000000000100000000000000000;
  dst2.bits[2] = 0b00000000000000000000000000000000;
  dst2.bits[3] = 0b10000000000000000000000000000000;

  s21_decimal d22;
  int error = s21_mul(dst1, dst2, &d22);

  // int qqqq = 0;
  // s21_from_decimal_to_int(d22, &qqqq);
  ck_assert_int_eq(error, 2);
}
END_TEST

// START_TEST(s21_mul_2) {
//   s21_decimal dec1 = {{100, 0, 0, 0}};     // 100
//   s21_decimal dec2 = {{999999, 0, 0, 0}};  // 9999.99
//   //s21_set_scale(&dec2, 2);
//   s21_set_exp(dec2, &dec2, 2);
//   s21_decimal res1;
//   s21_mul(dec1, dec2, &res1);
//   float g;
//   s21_from_decimal_to_float(res1, &g);
//   ck_assert_float_eq(g, 999999);
// }
// END_TEST

// START_TEST(s21_mul_3) {
//   s21_decimal dec1 = {{100, 0, 0, 0}};  // -100
//   s21_set_bit_V2(&dec1, 127, 1);
//   s21_decimal dec2 = {{999999, 0, 0, 0}};  // 9999.99
//   //s21_set_scale(&dec2, 2);
//   s21_set_exp(dec2, &dec2, 2);
//   s21_decimal res1;
//   s21_mul(dec1, dec2, &res1);

//   float g;
//   s21_from_decimal_to_float(res1, &g);
//   ck_assert_float_eq(g, -999999);
// }
// END_TEST

START_TEST(s21_mul_4) {
  s21_decimal dec1 = {{1002, 0, 0, 0}};  // -100.2
  // s21_set_scale(&dec1, 1);
  s21_set_exp(dec1, &dec1, 1);
  s21_set_bit_V2(&dec1, 127, 1);

  s21_decimal dec2 = {{999999, 0, 0, 0}};  // -9999.99
  // s21_set_scale(&dec2, 2);
  s21_set_exp(dec2, &dec2, 2);
  s21_set_bit_V2(&dec2, 127, 1);

  s21_decimal res1;
  s21_mul(dec1, dec2, &res1);
  float g;
  s21_from_decimal_to_float(res1, &g);
  ck_assert_float_eq_tol(g, 1001998.998, 1e-06);
}
END_TEST

START_TEST(s21_mul_5) {
  s21_decimal dec1 = {{0, 0, 0, 0}};  // -0.0
  // s21_set_scale(&dec1, 1);
  s21_set_exp(dec1, &dec1, 1);
  s21_set_bit_V2(&dec1, 127, 1);

  s21_decimal dec2 = {{999999, 0, 0, 0}};  // -9999.99
  // s21_set_scale(&dec2, 2);
  s21_set_exp(dec2, &dec2, 2);
  s21_set_bit_V2(&dec2, 127, 1);

  s21_decimal res1;
  s21_mul(dec1, dec2, &res1);
  int g;
  s21_from_decimal_to_int(res1, &g);
  float r = (float)g * pow(10, -s21_get_exp(res1));
  ck_assert_float_eq(r, 0.0);
}
END_TEST

START_TEST(s21_mul_too_big) {
  s21_decimal dec1 = {{BIT_SIZE - 1, BIT_SIZE - 1, BIT_SIZE - 1, 0}};
  s21_decimal dec2 = {{2, 0, 0, 0}};

  s21_decimal res;
  int ret = s21_mul(dec1, dec2, &res);

  ck_assert_int_eq(ret, 1);
}
END_TEST

START_TEST(s21_mul_rounding) {
  s21_decimal dec1 = {{123456789, 0, 0, 0}};
  // s21_set_scale(&dec1, 10);
  s21_set_exp(dec1, &dec1, 10);
  s21_decimal dec2 = {{123456789, 0, 0, 0}};
  // s21_set_scale(&dec2, 10);
  s21_set_exp(dec2, &dec2, 10);

  s21_decimal res;
  s21_mul(dec1, dec2, &res);
  float g;
  s21_from_decimal_to_float(res, &g);
  ck_assert_float_eq_tol(g, 0.00015241578512359410524368286132812, 1e-06);
}
END_TEST

START_TEST(s21_mul_too_big_neg) {
  s21_decimal dec1 = {{BIT_SIZE - 1, BIT_SIZE - 1, BIT_SIZE - 1, 0}};
  s21_set_bit_V2(&dec1, 127, 1);
  s21_decimal dec2 = {{2, 0, 0, 0}};

  s21_decimal res;
  int ret = s21_mul(dec1, dec2, &res);

  ck_assert_int_eq(ret, 2);
}
END_TEST

// START_TEST(test_mul_1) {
//   s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
//   s21_decimal val2 = {{2, 0, 0, 0}};
//   s21_decimal res = {{0}};
//   ck_assert_int_eq(0, s21_mul(val1, val2, &res));
// }
// END_TEST

// START_TEST(test_mul_2) {
//   s21_decimal val1 = {{2, 0, 0, 0}};
//   s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
//   s21_decimal res = {{0, 0, 0, 0}};
//   ck_assert_int_eq(0, s21_mul(val1, val2, &res));
// }
// END_TEST

// START_TEST(test_mul_3) {
//   s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
//   s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
//   s21_decimal res = {{0}};
//   ck_assert_int_eq(0, s21_mul(val1, val2, &res));
// }
// END_TEST

// START_TEST(test_mul_4) {
//   s21_decimal val1 = {{2, 0, 0, 0}};
//   s21_decimal val2 = {{2, 0, 0, 0}};
//   s21_decimal res = {{4, 0, 0, 0}};

//   int a = s21_mul(val1, val2, &res);
//   printf("\n\n\na = %d\n\n\n", a);
//   ck_assert_int_eq(0, a);
// }
// END_TEST

// START_TEST(test_mul_5) {
//   s21_decimal val1 = {{8, 0, 0, 0}};
//   s21_decimal val2 = {{2, 0, 0, 0}};
//   s21_decimal res = {{0}};
//   ck_assert_int_eq(0, s21_mul(val1, val2, &res));
// }
// END_TEST

// START_TEST(test_mul_6) {
//   s21_decimal val1 = {{2, 0, 0, 0}};
//   s21_decimal val2 = {{8, 0, 0, 0}};
//   s21_decimal res = {{0}};
//   ck_assert_int_eq(0, s21_mul(val1, val2, &res));
// }
// END_TEST

// START_TEST(test_mul_7) {
//   s21_decimal val1 = {{8, 0, 0, ~(UINT_MAX / 2)}};
//   s21_decimal val2 = {{2, 0, 0, 0}};
//   s21_decimal res = {{0}};
//   ck_assert_int_eq(0, s21_mul(val1, val2, &res));
// }
// END_TEST

// START_TEST(test_mul_8) {
//   s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
//   s21_decimal val2 = {{8, 0, 0, 0}};
//   s21_decimal res = {{0}};
//   ck_assert_int_eq(0, s21_mul(val1, val2, &res));
// }
// END_TEST

START_TEST(test_mul_9) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

// START_TEST(test_mul_10) {
//   s21_decimal value_1 = {{5, 0, 0, 0}};
//   s21_decimal value_2 = {{7, 0, 0, 0}};
//   s21_decimal result = {{0, 0, 0, 0}};
//   s21_decimal check = {{35, 0, 0, 0}};
//   int return_value = s21_mul(value_1, value_2, &result);
//   ck_assert_int_eq(s21_is_equal(result, check), 1);
//   ck_assert_int_eq(return_value, 0);
// }
// END_TEST

START_TEST(test_mul_11) {
  s21_decimal src1, src2;
  int a = -32768;
  int b = 32768;
  int res_our_dec = 0;
  s21_from_int_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  int res_origin = -1073741824;
  s21_decimal res_od = {0};
  s21_mul(src1, src2, &res_od);
  s21_from_decimal_to_int(res_od, &res_our_dec);
  ck_assert_int_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(test_mul_12) {
  int num1 = -10;
  int num2 = -10;
  int prod_int = 100;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_mul(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, prod_int);
}
END_TEST

START_TEST(test_mul_13) {
  int num1 = 10;
  int num2 = 20;
  int prod_int = 200;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_mul(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, prod_int);
}
END_TEST

START_TEST(test_mul_14) {
  int num1 = -10;
  int num2 = 20;
  int prod_int = -200;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_mul(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, prod_int);
}
END_TEST

START_TEST(test_mul_15) {
  int num1 = 9403;
  int num2 = 202;
  int res_origin = 1899406;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_mul(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(test_mul_16) {
  int num1 = -32768;
  int num2 = 2;
  int res_origin = -65536;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_mul(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(test_mul_17) {
  int num1 = -32768;
  int num2 = 32768;
  int res_origin = -1073741824;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_mul(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(test_mul_18) {
  int num1 = -32768;
  int num2 = 32768;
  int res_origin = 0;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_set_exp(a, &a, 20);
  s21_set_exp(b, &b, 20);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_mul(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

Suite *suite_mul(void) {
  Suite *s;
  TCase *tc;
  s = suite_create("s21_mul");
  tc = tcase_create("case_mul");

  tcase_add_test(tc, mul_test_1);  // ggggggg (все сыпятся)
  tcase_add_test(tc, mul_test_2);
  tcase_add_test(tc, mul_test_3);
  tcase_add_test(tc, mul_test_4);
  tcase_add_test(tc, mul_test_5);
  tcase_add_test(tc, mul_test_6);
  // tcase_add_test(tc, mul_test_7);
  tcase_add_test(tc, mul_test_8);  //не проходит? когда включаем
  tcase_add_test(tc, s21_mul_1);
  tcase_add_test(tc, s21_mul_big_1);
  tcase_add_test(tc, s21_mul_big_2);
  // tcase_add_test(tc, s21_mul_2);
  // tcase_add_test(tc, s21_mul_3);
  tcase_add_test(tc, s21_mul_4);
  tcase_add_test(tc, s21_mul_5);
  tcase_add_test(tc, s21_mul_too_big);
  tcase_add_test(tc, s21_mul_too_big_neg);
  tcase_add_test(tc, s21_mul_rounding);

  // tcase_add_test(tc, test_mul_1);
  // tcase_add_test(tc, test_mul_2);
  // tcase_add_test(tc, test_mul_3);
  // tcase_add_test(tc, test_mul_4);
  // tcase_add_test(tc, test_mul_5);
  // tcase_add_test(tc, test_mul_6);
  // tcase_add_test(tc, test_mul_7);
  // tcase_add_test(tc, test_mul_8);
  tcase_add_test(tc, test_mul_9);
  // tcase_add_test(tc, test_mul_10);
  tcase_add_test(tc, test_mul_11);
  tcase_add_test(tc, test_mul_12);
  tcase_add_test(tc, test_mul_13);
  tcase_add_test(tc, test_mul_14);
  tcase_add_test(tc, test_mul_15);
  tcase_add_test(tc, test_mul_16);
  tcase_add_test(tc, test_mul_17);
  tcase_add_test(tc, test_mul_18);

  suite_add_tcase(s, tc);
  return s;
}