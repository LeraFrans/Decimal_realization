#include "s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
    int res = 1;
    if(dst != NULL && src.bits[1] == 0 && src.bits[2] == 0)
    {
        int temp = 0;
        s21_from_decimal_to_int(src, &temp);
        int exp = s21_get_exp(src);
        char str[12] = {0};
        sprintf(str, "%d", temp);
        int exposition = strlen(str) - exp;
        for (int i = strlen(str); i >= exposition; i-- ) {
           str[i] = str[i-1];
           if (i == exposition) str[i] = '.'; 
        }
        *dst = temp * pow(0.1, exp);
        //printf("exp = %d\n", exp);
        //printf("dest = %f\n", *dst);
        res = 0;
    }

    return res;
}
