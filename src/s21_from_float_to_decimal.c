#include"s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
    int res = 0;
    if(dst != NULL) {
    s21_decimal a = {50, 0, 0, 0};
    int num[30] = {0};
    char str[100] = "";
    sprintf(str, "%+e", src);
    int count_int = 0;
    int count_str = 0;
    int count_exp = 0;
    int p = 0;
    int e = 0;
    int neg = 0;
    int neg_int = 0;
    int total_int = 0;

    // //    for(int count_p = 0; count_p <100; count_p++) {
    // //     printf("%c", str[count_p]);
    // // }   
    // //     printf("%c",'\n');
    // Бежим по строке, пока не встретим букву е
    for(count_str; str[count_str] != 'e'; count_str++) {
        if (str[count_str] != '.' && str[count_str] != '+' && str[count_str] != '-') {
            num[count_int] = str[count_str] - '0';
            count_exp++;
            count_int++;
        }else if(str[count_str] == '-') {
            neg_int = 1;
        } else {count_exp = 0;
        }
    }
    ///printf("str: %s\n", str);
    // printf("%c",'\n');
    // Продолжаем бежать по строке, пока она не кончится
    for(count_str; str[count_str] != '\0'; count_str++) {
    if (str[count_str] == '-') neg = 1;
    if (str[count_str] != 'e' && str[count_str] != '-' && str[count_str] != '+' ) {
        e += (str[count_str] - '0');
        p++;}
    }
    if (neg == 1) e *= -1;
    if (count_exp == count_int) count_exp = 0;
    int count_pow = 0;
    while ((--count_int) >= 0) {
      total_int += (num[count_int] * pow(10, count_pow));
      //printf("num: %d\n", num[count_int]);
      count_pow++;
      //printf("total_num: %d\n", total_int);
    }
    if (neg_int == 1) total_int *= -1;
    s21_from_int_to_decimal(total_int, &a);
    s21_set_exp(a, dst, count_exp - e);
    }
    
    return res;
}
