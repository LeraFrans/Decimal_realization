#include"s21_decimal.h"

//help

/** @brief Set bit on position in decimal
 *
 *
 *  @param value the decimal
 *  @param result the decimal after set bit
 *  @param position the number of bit in decimal in diapason 0 - 127
 *  @return 0 if bit is set, 1 if result == NULL or 0 > position > 127
 */
int s21_set_bit(s21_decimal value, s21_decimal *result, int position) { //0 - OK, 1 - ERROR, position 0-127
    int res = OK;
    if((result != NULL) && (position > -1 && position < 128)) {
        s21_cpy_decimal(value, result);

        int byte = position / 32;
        int bit = position % 32;
        //printf("byte: %d bit: %d ", byte, bit);
        result->bits[byte] |= (1 << bit);
    } else res = 1;

    return res;
}

/** @brief Get bit 0 or 1 on position in decimal
 *
 *
 *  @param value the decimal
 *  @param position the number of bit in decimal in diapason 0 - 127
 *  @return Bit 0 or 1 on position or -1 in error case 0 > position > 127
 */
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

/** @brief Set scale for decimal without changing mantissa
 *
 *
 *  @param value the decimal
 *  @param result the decimal after set scale
 *  @param exp scale for set
 *  @return 0 in case of sucsess and 1 in case of error when 0 > exp > 28
 */
int s21_set_exp(s21_decimal value, s21_decimal *result, int exp) {  // 0 - OK, 1 - ERROR
    int res = 1;
    int sign = 0;
    if(exp >= 0 && exp <= 28) {
        s21_cpy_decimal(value, result);
        sign = s21_get_bit(value, 127);
        exp = exp << 16;
        result->bits[3] = exp;
        if(sign) s21_negate(*result, result);
        res = 0;
    }

    return res;
}

/** @brief Get scale of decimal
 *
 *
 *  @param value the decimal
 *  @return The scale of decimal
 */
/*
int s21_get_exp(s21_decimal value) {
    value.bits[3] = value.bits[3] << 1;
    value.bits[3] = value.bits[3] >> 17;
    
    return value.bits[3];
}
*/

/** @brief Invert bit on current position in decimal
 *
 *
 *  @param value the decimal
 *  @param result the decimal after invert of bit
 *  @param position the position of bit in decimal for invert
 *  @return 0 in case of sucsess and 1 in case of error when result == NULL or 0 > position > 127
 */
int s21_invert_bit(s21_decimal value, s21_decimal *result, int position) {  // 0 - OK, 1 - ERROR
    int res = 1;
    if((result != NULL) && (position > -1 && position < 128)) {
        s21_cpy_decimal(value, result);

        int byte = position / 32;
        int bit = position % 32;
        //printf("byte: %d bit: %d ", byte, bit);
        result->bits[byte] ^= (1 << bit);
        res = 0;
    }
    return res;
}

int s21_get_additional_code(s21_decimal value, s21_decimal* result) {
    if(result == NULL) return NULL_POINTER_EXEPTION;
    for (int i = 0; i < 3; i++)
        result->bits[i] = ~value.bits[i];
    result->bits[3] = value.bits[3];
    //s21_invert_bit(*result, result, 127);
    //printf("invert b:\n");
    //s21_print_decimal(*result);
    s21_sum_mantissa(*result, (s21_decimal){1, 0, 0, 0}, result);
    //printf("b + 1:\n");
    //s21_print_decimal(*result);
    
    
    return 0;
}

/** @brief Retern position of last bit equals 1 from end of decimal
 *
 *
 *  @param value the decimal
 *  @return position of bit
 */
int s21_get_last_bit(s21_decimal value) {
    int bit = 0;
    for (int i = 0; i < 96; i++)
    {
        if(s21_get_bit(value, i) == 1) bit = i;
    }
    
    return bit;
}

/** @brief Copy decimal from src to dest
 *
 *
 *  @param scr copy from
 *  @param dest copy to
 */
void s21_cpy_decimal(s21_decimal src, s21_decimal* dest) {
    for (int i = 0; i < 4; i++)
        dest->bits[i] = src.bits[i];
    
}

int s21_cpy_decimal_to_big_decimal(s21_decimal src, s21_big_decimal *dst) { //0 - OK, 1 - ERROR
    int res = OK;
    if(dst != NULL) {
        for(int i = 0; i < 3; i++)
            dst->bits[i] = src.bits[i];
        
        for(int i = 3; i < 7; i++)
            dst->bits[i] = 0;

        dst->bits[7] = src.bits[3];
        
    } else res = NULL_POINTER_EXEPTION;
    return res;
}

int s21_is_correct_decimal(s21_decimal value) { //0 - OK, 1 - error in zero bits, 2 - wrong exp ?????????????
    unsigned int byte = value.bits[3];
    unsigned int mask = 0x7f00ffff;
    int result = 0;
    printf("byte before: %x\n", byte);
    if((byte & mask) != 0) result = 1;
    if(((byte << 8) >> 24) > 28) result = 2;
    printf("byte: %x\n", byte);
    return result;
}

/** @brief Set all bits in value zero
 *
 *
 *  @param value the decimal
 *  @return 0 in case of sucsess and 1 in case of error(value == NULL)
 */
int s21_init_zero_decimal(s21_decimal *value) { //0 - OK, 1 - ERROR 
    if(value == NULL) return NULL_POINTER_EXEPTION;
    for (int i = 0; i < 4; i++)
        value->bits[i] = 0;
    
    return OK;
}

/** @brief Print decimal 
 *
 *
 *  @param value the decimal
 */
void s21_print_decimal(s21_decimal value) {
    for (int i = 127; i >= 0; i--) {
        if((i + 1) % 32 == 0) printf("|\n");
        printf("%d ", s21_get_bit(value, i));
    }
    printf("\n");
    
}

/** @brief Check decimal is zero
 *
 *
 *  @param value decimal
 *  @return 0 in case of decimal is zero
 */
int s21_is_zero(s21_decimal value) {
    return  !(value.bits[0] == 0 &&
            value.bits[1] == 0 &&
            value.bits[2] == 0);
}

// convert

/** @brief Convert integer to decimal
 *
 *
 *  @param src integer
 *  @param dst decimal
 *  @return 0 in case of sucsess and 1 in case of error(dst == NULL)
 */
int s21_from_int_to_decimal(int src, s21_decimal *dst) {
    int res = OK;
    s21_decimal dcml = {0};
    if(dst != NULL) {
        for (int i = 0; i < 4; i++)
            dst->bits[i] = 0;
        
        if(src < 0) {
            s21_set_bit(dcml, dst, 127);    // set sign bit
            src *= -1;
        }
        dst->bits[0] = src;
    } else res = NULL_POINTER_EXEPTION;

    return res;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {    //todo exp
    int res = 1;
    if(dst != NULL && src.bits[1] == 0 && src.bits[2] == 0) {   //check pointer and value
        *dst = src.bits[0];
        if(s21_get_bit(src, 127) == 1) *dst *= -1;

    } else res = 0;

    return res;
}



//other
// int s21_truncate(s21_decimal value, s21_decimal *result) {
//     return 0;
// }

/** @brief Change sign of decimal
 *
 *
 *  @param value decimal
 *  @param result decimal after change sign
 *  @return 0 in case of sucsess and 1 in case of error(result == NULL)
 */
int s21_negate(s21_decimal value, s21_decimal *result) { // 0 - OK, 1 - ERROR
    
    return s21_invert_bit(value, result, 127);
}

//arirhmetic

// int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
//     int res = 0;
//     int result_exp = 0;
//     int exp_1 = s21_get_exp(value_1);
//     int exp_2 = s21_get_exp(value_2);
//     s21_big_decimal bvalue_1 = {0};
//     s21_big_decimal bvalue_2 = {0};
//     res += s21_cpy_decimal_to_big_decimal(value_1, &bvalue_1);
//     res += s21_cpy_decimal_to_big_decimal(value_2, &bvalue_2);
//     //result_exp = max(exp_1, exp_2);


//     return res;
// }

// int s21_badd(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
//     s21_big_decimal bvalue_1 = {0};
//     s21_big_decimal bvalue_2 = {0};
    
//     return 0;
// }

// int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {

//     return 0;
// }


int s21_minus_positiv_mantissa(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    if(result == NULL) return NULL_POINTER_EXEPTION;
    s21_decimal max_mantisa = {S21_MAX_UINT, S21_MAX_UINT, S21_MAX_UINT, 0};
    //if (s21_compare_mantissa(value_1, max_mantisa)) return S21_OVERFLOW;
    int bit_1 = 0, bit_2 = 0, next_bit = 0;
    int end = s21_get_last_bit(value_1);
    s21_init_zero_decimal(result);
    if(s21_compare_mantissa(value_1, value_2) == 2) s21_negate(*result, result);
    for (int i = 0; i <= end; i++) {
        bit_1 = s21_get_bit(value_1, i);
        bit_2 = s21_get_bit(value_2, i);
        if(bit_1 == 1 && bit_2 == 0 && next_bit == 0) {
            s21_set_bit(*result, result, i);
        }
        if(bit_1 == 0 && bit_2 == 0 && next_bit == 1) {
            s21_set_bit(*result, result, i);
        }
        if(bit_1 == 1 && bit_2 == 1 && next_bit == 1) {
            s21_set_bit(*result, result, i);
            next_bit = 1;
        }
        if(bit_1 == 0 && bit_2 == 1 && next_bit == 0) {
            next_bit = 1;
            s21_set_bit(*result, result, i);
        }
        if(bit_1 == 1 && bit_2 == 0 && next_bit == 1) {
            next_bit = 0;
        }

    }
    result->bits[3] = value_1.bits[3];
    
    return OK;
}

/** @brief Adds mantises of two decimal with equals scale
 *
 *
 *  @param value_1 decimal
 *  @param value_2 decimal
 *  @param result decimal after add mantises
 *  @return 0 in case of sucsess, 1 in case of result == NULL, 2 in case of wrong scale, 3 in case of S21_OVERFLOW mantissa
 */
int s21_sum_mantissa(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {   // 0 - OK, 1 - null pointer, 2 - wrong exp, 3 - S21_OVERFLOW
    int next = 0;
    int sign_next = 0;
    int bit_1 = 0, bit_2 = 0;
    if(s21_init_zero_decimal(result) != 0) return NULL_POINTER_EXEPTION;    //result is NULL
    if(s21_set_exp(*result, result, s21_get_exp(value_1)) != 0) return EXPONENT_EXEPTION;  //wrong exp
    //test
    
    if(s21_get_bit(value_1, 127) == 1) s21_get_additional_code(value_1, &value_1);
    if(s21_get_bit(value_2, 127) == 1) s21_get_additional_code(value_2, &value_2);
    //printf("additional b:\n");
    //s21_print_decimal(value_2);
    //end
    for (int i = 0; i < 96; i++) {
        bit_1 = s21_get_bit(value_1, i);
        bit_2 = s21_get_bit(value_2, i);
        next += bit_1 + bit_2;
        result->bits[i / 32] |= ((next % 2) << (i % 32));
        if(next == 1) next = 0;
        if(next > 1) next = 1;

        
    }
    //test for additional code
    sign_next = s21_get_bit(value_1, 127) + s21_get_bit(value_2, 127) + next;
    if(sign_next % 2 == 1) s21_set_bit(*result, result, 127);

    if(sign_next > 1) sign_next = 1;
    else sign_next = 0;

    if(next != sign_next) return S21_OVERFLOW;
    //end
    //if(next != 0) return OVERFLOW; //overflow mantissa
    result->bits[3] = value_1.bits[3];
    return OK;
}


/** @brief Divide two decimal
 *
 *
 *  @param value decimal
 */
void s21_div_two(s21_decimal *value) {
    int last_bit = 0;
    value->bits[0] >>= 1;
    last_bit = s21_get_bit(*value, 32);
    if(last_bit) s21_set_bit(*value, value, 31);
    value->bits[1] >>= 1;
    last_bit = s21_get_bit(*value, 64);
    if(last_bit) s21_set_bit(*value, value, 63);
    value->bits[2] >>= 1;
    
}

/** @brief Divide ten only mantissa of decimal
 *
 *
 *  @param value decimal
 *  @param result decimal after division
 *  @return 0 in case of sucsess, 3 in case of overflow mantissa(value doesn`t change)
 */
int s21_div_ten_mantissa(s21_decimal value, s21_decimal *result) {   //0 - OK, 3 - overflow
    int res = OK;
    
    return res;
}

/** @brief Multiply two decimal
 *
 *
 *  @param value decimal
 *  @return 0 in case of sucsess, 3 in case of overflow mantissa(value doesn`t change)
 */
int s21_mul_two(s21_decimal *value) {   //0 - OK, 3 - overflow
    int first_bit = s21_get_bit(*value, 95);
    if(first_bit == 1) return S21_OVERFLOW;

    value->bits[2] <<= 1;
    first_bit = s21_get_bit(*value, 63);
    if(first_bit) s21_set_bit(*value, value, 64);
    value->bits[1] <<= 1;
    first_bit = s21_get_bit(*value, 31);
    if(first_bit) s21_set_bit(*value, value, 32);
    value->bits[0] <<= 1;
    
    return OK;
}

/** @brief Raise to the power of 2 decimal
 *
 *
 *  @param value decimal
 *  @param pow power of 2
 *  @return 0 in case of sucsess, 3 in case of overflow mantissa(value doesn`t change)
 */
int s21_mul_two_pow(s21_decimal *value, int pow) {  //0 - OK, 3 - overflow
    s21_decimal a = *value;
    int res = OK;
    for (int i = 0; i < pow; i++) {
        if((res = s21_mul_two(&a)) == S21_OVERFLOW) {
            res = S21_OVERFLOW;
            break;
        }
    }
    if(res == OK) *value = a;

    return res;
}

/** @brief Multiply ten mantissa and scale of decimal
 *
 *
 *  @param value decimal
 *  @param result decimal after multiply
 *  @return 0 in case of sucsess, 3 in case of overflow mantissa(value doesn`t change)
 */
int s21_mul_ten_mantissa(s21_decimal value, s21_decimal *result) {   //0 - OK, 3 - overflow
    s21_decimal a = value;
    s21_decimal b = value;
    s21_decimal c = {0};
    int res = OK;

    for (int i = 0; i < 3; i++) {
        if(s21_mul_two(&a) != OK) {
            res = S21_OVERFLOW;
            break;
        }
    }

    if(res == OK && s21_mul_two(&b) == OK) {
        res = s21_sum_mantissa(a, b, &c);
    }
    if(res == OK && s21_increase_exp(c, &c) == OK)
        *result = c;
    else res = S21_OVERFLOW;
    
    return res;
}

/** @brief Increase scale if it possible
 *
 *
 *  @param value decimal
 *  @param result decimal after increase
 *  @return 0 in case of sucsess, 1 in case of wrong scale
 */
int s21_increase_exp(s21_decimal value, s21_decimal* result) {
    return s21_set_exp(value, result, s21_get_exp(value) + 1);
}

/** @brief Decrease scale if it possible
 *
 *
 *  @param value decimal
 *  @param result decimal after decrease
 *  @return 0 in case of sucsess, 1 in case of wrong scale
 */
int s21_decrease_exp(s21_decimal value, s21_decimal* result) {
    return s21_set_exp(value, result, s21_get_exp(value) - 1);
}


//compare

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
    // int sign_1 = s21_get_bit(value_1, 127);
    // int sign_2 = s21_get_bit(value_2, 127);

    int res = 1;

    for (int i = 0; i < 4; i++) {
        if (value_1.bits[i] != value_2.bits[i]) {
            res = 0;
            break;
        }
    }

    return res;

}


/** @brief Compare only mantissa of decimal(sign doesn't matter)
 *
 *
 *  @param value_1 decimal
 *  @param value_2 decimal
 *  @return 0 in case of decimals are equals, 1 in case value_1 > value_2, 2 in case value_2 > value_1
 */
int s21_compare_mantissa(s21_decimal value_1, s21_decimal value_2) {
    int res = 0;
    int equals = 1;
    //if(s21_is_zero(value_1) == 0 && s21_is_zero(value_2) == 0) return 0;
    for (int i = 95; i >= 0; i--) {
        if(s21_get_bit(value_1, i) > s21_get_bit(value_2, i)) res = 1;
        if(s21_get_bit(value_1, i) < s21_get_bit(value_2, i)) res = 2;
        if(res) break;
    }

    return res;
}
/*
int main() {
    s21_decimal a = {50, 0, 0, 0};
    s21_decimal b = {49, 0, 0, 0};
    s21_decimal c = {0, 0, 0, 0};
    
    s21_negate(b, &b);
    printf("a: \n");
    s21_print_decimal(a);
    printf("b :\n");
    s21_print_decimal(b);
    printf("res sum: %d\n", s21_sum_mantissa(a, b, &c));
    s21_print_decimal(c);

    return 0;
}
*/
//10000010
//01111011
//       0 

//0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 |1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 |1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 |1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 0 0 1 1 1 1 
//0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 |0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 |0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 |0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 1 0 0 1 0
