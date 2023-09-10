#include "tests_suitcases.h"

START_TEST(s21_from_float_to_decimal_1) {
  s21_decimal val;
  float fl1 = 3;
  float fl2 = 127.1234;
  float fl1_res = 0;
  float fl2_res = 0;
  s21_from_float_to_decimal(fl1, &val);
  s21_from_decimal_to_float(val, &fl1_res);
  ck_assert_double_eq_tol(fl1, fl1_res, 1e-28);
  s21_from_float_to_decimal(fl2, &val);
  s21_from_decimal_to_float(val, &fl2_res);
  ck_assert_double_eq_tol(fl2, fl2_res, 1e-28);
}
END_TEST

START_TEST(s21_from_float_to_decimal_2) {
  s21_decimal val;
  float fl1 = -128.023;
  float fl2 = 12345.37643764;
  float fl1_res = 0;
  float fl2_res = 0;
  s21_from_float_to_decimal(fl1, &val);
  s21_from_decimal_to_float(val, &fl1_res);
  ck_assert_double_eq_tol(fl1, fl1_res, 1e-28);
  s21_from_float_to_decimal(fl2, &val);
  s21_from_decimal_to_float(val, &fl2_res);
  ck_assert_double_eq_tol(fl2, fl2_res, 1e-28);
}
END_TEST
START_TEST(s21_from_float_to_decimal_3) {
  s21_decimal val;
  float num = -2.1474836E+09;
  s21_from_float_to_decimal(num, &val);
  ck_assert_int_eq(val.bits[0], 2147483648);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 2147483648);
}
END_TEST

START_TEST(s21_from_float_to_decimal_4) {
  s21_decimal val;
  float fl1 = 22.14836E+03;
  float fl2 = -2.1474836E+09;
  float fl1_res = 0;
  float fl2_res = 0;

  s21_from_float_to_decimal(fl1, &val);
  s21_from_decimal_to_float(val, &fl1_res);
  ck_assert_double_eq_tol(fl1, fl1_res, 1e-28);

  s21_from_float_to_decimal(fl2, &val);
  s21_from_decimal_to_float(val, &fl2_res);
  ck_assert_double_eq_tol(fl2, fl2_res, 1e-28);
}
END_TEST

START_TEST(s21_from_float_to_decimal_5) {
  s21_decimal val;
  s21_from_float_to_decimal(1.02E+09, &val);
  ck_assert_int_eq(val.bits[0], 1020000000);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);
}
END_TEST

// START_TEST(s21_from_float_to_decimal_6) {
//   s21_decimal val;
//   float fl1 = -333.2222;
//   float fl2 = -2.1474836E+20;
//   float fl1_res = 0;
//   float fl2_res = 0;

//   s21_from_float_to_decimal(fl1, &val);
//   s21_from_decimal_to_float(val, &fl1_res);
//   ck_assert_double_eq_tol(fl1, fl1_res, 1e-28);

//   s21_from_float_to_decimal(fl2, &val);
//   s21_from_decimal_to_float(val, &fl2_res);
//   ck_assert_double_eq_tol(fl2, fl2_res, 1e-28);
// }
// END_TEST

// START_TEST(s21_from_float_to_decimal_7) {
//   printf("\nHHHHHHHHHHHHHHHHH\n");
//   s21_decimal val;
//   float a = 1.0 / 0.0;
//   s21_from_float_to_decimal(a, &val);
//   ck_assert_int_eq(val.bits[0], 0);
//   ck_assert_int_eq(val.bits[1], 0);
//   ck_assert_int_eq(val.bits[2], 0);
//   ck_assert_int_eq(val.bits[3], 0);
// }
// END_TEST

// START_TEST(s21_from_float_to_decimal_8) {
//   s21_decimal val;
//   float a = -1.0 / 0.0;
//   s21_from_float_to_decimal(a, &val);
//   ck_assert_int_eq(val.bits[0], 0);
//   ck_assert_int_eq(val.bits[1], 0);
//   ck_assert_int_eq(val.bits[2], 0);
//   ck_assert_int_eq(val.bits[3], 0);
// }
// END_TEST

// START_TEST(s21_from_float_to_decimal_10) {
//   printf("\nHHHHHHHHHHHHHHHHH\n");
//   s21_decimal val;
//   float a = 1e-30;
//   s21_from_float_to_decimal(a, &val);
//   ck_assert_int_eq(val.bits[0], 0);
//   ck_assert_int_eq(val.bits[1], 0);
//   ck_assert_int_eq(val.bits[2], 0);
//   ck_assert_int_eq(val.bits[3], 0);
// }
// END_TEST

START_TEST(s21_from_float_to_decimal_11) {
  printf("\nHHHHHHHHHHHHHHHHH\n");
  s21_decimal dec;
  float tmp = 0;
  float tmp1 = 0.03;
  s21_from_float_to_decimal(tmp1, &dec);
  s21_from_decimal_to_float(dec, &tmp);
  ck_assert_float_eq_tol(tmp, tmp1, 1e-06);
}
END_TEST

START_TEST(s21_from_float_to_decimal_12) {
  s21_decimal dec;
  s21_from_float_to_decimal(-128.023, &dec);
  float tmp = 0;
  s21_from_decimal_to_float(dec, &tmp);
  ck_assert_float_eq_tol(tmp, -128.023, 1e-06);
}
END_TEST

START_TEST(s21_from_float_to_decimal_13) {
  s21_decimal dec;
  s21_from_float_to_decimal(-2.1474836E+09, &dec);
  float tmp = 0;
  s21_from_decimal_to_float(dec, &tmp);
  ck_assert_float_eq_tol(tmp, -2.1474836E+09, 1e-06);
}
END_TEST

START_TEST(s21_from_float_to_decimal_14) {
  s21_decimal dec;
  s21_from_float_to_decimal(22.14836E+03, &dec);
  float tmp = 0;
  s21_from_decimal_to_float(dec, &tmp);
  ck_assert_float_eq_tol(tmp, 22.14836E+03, 1e-06);
}
END_TEST

START_TEST(s21_from_float_to_decimal_15) {
  s21_decimal dec;
  s21_from_float_to_decimal(1.02E+08, &dec);
  float tmp = 0;
  s21_from_decimal_to_float(dec, &tmp);
  ck_assert_float_eq_tol(tmp, 1.02E+08, 1e-06);
}
END_TEST

START_TEST(s21_from_float_to_decimal_16) {
  s21_decimal dec;
  s21_from_float_to_decimal(-333.2222, &dec);
  float tmp = 0;
  s21_from_decimal_to_float(dec, &tmp);
  ck_assert_float_eq_tol(tmp, -333.2222, 1e-06);
}
END_TEST

// START_TEST(s21_from_float_to_decimal_17) {
//   s21_decimal dec;
//   float a = 1.0 / 0.0;
//   int ret = s21_from_float_to_decimal(a, &dec);
//   ck_assert_int_eq(ret, 1);
// }
// END_TEST

// START_TEST(s21_from_float_to_decimal_18) {
//   s21_decimal dec;
//   float a = -1.0 / 0.0;
//   s21_from_float_to_decimal(a, &dec);
//   ck_assert_int_eq(dec.bits[0], 0);
//   ck_assert_int_eq(dec.bits[1], 0);
//   ck_assert_int_eq(dec.bits[2], 0);
//   ck_assert_int_eq(dec.bits[3], 0);
// }
// END_TEST

Suite *suite_from_float_to_decimal(void) {
  Suite *s;
  TCase *tc;
  s = suite_create("s21_from_float_to_decimal");
  tc = tcase_create("case_from_float_to_decimal");

  tcase_add_test(tc, s21_from_float_to_decimal_1);
  printf("\n1\n\n");
  tcase_add_test(tc, s21_from_float_to_decimal_2);
  printf("\n2\n\n");
  tcase_add_test(tc, s21_from_float_to_decimal_3);
  printf("\n3\n\n");
  tcase_add_test(tc, s21_from_float_to_decimal_4);
  printf("\n4\n\n");
  tcase_add_test(tc, s21_from_float_to_decimal_5);
  printf("\n5\n\n");
  //tcase_add_test(tc, s21_from_float_to_decimal_6);
  printf("\n6\n\n");
  //tcase_add_test(tc, s21_from_float_to_decimal_7);
  printf("\n7\n\n");
  //tcase_add_test(tc, s21_from_float_to_decimal_8);
  printf("\n\n8\n\n");
  //tcase_add_test(tc, s21_from_float_to_decimal_10);
  printf("\n9\n\n");
  tcase_add_test(tc, s21_from_float_to_decimal_11);
  printf("\n10\n\n");
  tcase_add_test(tc, s21_from_float_to_decimal_12);
  printf("\n11\n\n");
  tcase_add_test(tc, s21_from_float_to_decimal_13);
  printf("\n12\n\n");
  tcase_add_test(tc, s21_from_float_to_decimal_14);
  printf("\n13\n\n");
  tcase_add_test(tc, s21_from_float_to_decimal_15);
  printf("\n14\n\n");
  tcase_add_test(tc, s21_from_float_to_decimal_16);
  printf("\n15\n\n");
  //tcase_add_test(tc, s21_from_float_to_decimal_17);
  printf("\n16\n\n");
  //tcase_add_test(tc, s21_from_float_to_decimal_18);
  printf("\n17\n\n");

  suite_add_tcase(s, tc);
  return s;
}
