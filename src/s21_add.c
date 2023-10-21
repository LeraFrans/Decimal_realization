#include "s21_decimal.h"

/** @brief Adds two decimal, the result of the addition is writen into result
 *
 *
 *  @param value_1 first decimal
 *  @param value_2 second decimal
 *  @param result resulting decimal
 *  @return 0 - OK.  
            1 - the number is too large or equal to infinity.  
            2 - the number is too small or equal to negative infinity.  
 */
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {

  //firs check of value validity  
  int error = 0;
  error = s21_owerflow_before_normalization_for_add(value_1, value_2);
  if (error != 0) return error;
  error = s21_check_exponenta(value_1, value_2);
  if (error != 0) return error;


  int res = 0;
  s21_decimal res_first = {0};  //first decimal after normalization
  s21_decimal res_second = {0}; //second decimal after normalization

  //if accuracy is lost during the normalization, we will write the cut of part into "remaind" 
  int remaind_1[30] = {0};
  int remaind_2[30] = {0};
  s21_normalization(value_1, value_2, &res_first, &res_second, remaind_1,
                    remaind_2);

  //Check signs and make subtraction or addition.
  //After that make banking round. (Edit res if owerflow)

  //if both are positive
  if (s21_get_bit(res_first, 127) == 0 && s21_get_bit(res_second, 127) == 0) {
    if (s21_sum_mantissa(res_first, res_second, result) == 3) res = 1;
    if (s21_banking_round_for_add(remaind_1, remaind_2, result) == 1) res = 1;
  }

  //if both are negative
  else if (s21_get_bit(value_1, 127) == 1 && s21_get_bit(value_2, 127) == 1) {
    s21_set_bit_V2(&res_first, 127, 0);
    s21_set_bit_V2(&res_second, 127, 0);
    if (s21_sum_mantissa(res_first, res_second, result) == 3) res = 2;
    if (s21_banking_round_for_add(remaind_1, remaind_2, result) == 1) res = 2;
    s21_set_bit_V2(result, 127, 1);
  }

  //if only first are negative
  else if (s21_get_bit(res_first, 127) == 1 &&
           s21_get_bit(res_second, 127) == 0) {
    s21_set_bit_V2(&res_first, 127, 0);
    //the module of the first are greater
    if (s21_compare_mantissa(res_first, res_second) == 1) {
      if (s21_minus_positiv_mantissa(res_first, res_second, result) == 3)
        res = 2;
      if (s21_banking_round_for_sub(remaind_1, remaind_2, result) == 1) res = 2;
      s21_set_bit_V2(result, 127, 1);
    }
    //the module of the second are greater
    else if (s21_compare_mantissa(res_first, res_second) == 2 ||
             s21_compare_mantissa(res_first, res_second) == 0) {
      if (s21_minus_positiv_mantissa(res_second, res_first, result) == 3)
        res = 1;
      if (s21_banking_round_for_sub(remaind_2, remaind_1, result) == 1) res = 1;
    }
  }

  //if only second are nagative
  else if (s21_get_bit(res_first, 127) == 0 &&
           s21_get_bit(res_second, 127) == 1) {
    s21_set_bit_V2(&res_second, 127, 0);
    //the module of the second are greater
    if (s21_compare_mantissa(res_first, res_second) == 2) {
      if (s21_minus_positiv_mantissa(res_second, res_first, result) == 3)
        res = 2;
      if (s21_banking_round_for_sub(remaind_2, remaind_1, result) == 1) res = 2;
      s21_set_bit_V2(result, 127, 1);
    }
    //the module of the first are greater
    else if (s21_compare_mantissa(res_first, res_second) == 1 ||
             s21_compare_mantissa(res_first, res_second) == 0) {
      if (s21_minus_positiv_mantissa(res_first, res_second, result) == 3)
        res = 1;
      if (s21_banking_round_for_sub(remaind_1, remaind_2, result) == 1) res = 1;
    }
  }

  return res;
}



/** @brief Checks for owerflow before normalization changes the mantissa
 *
 *
 *  @param value_1 first decimal
 *  @param value_2 second decimal
 *  @return 0 - OK.  
            1 - the number is too large or equal to infinity.  
            2 - the number is too small or equal to negative infinity.  
 */
int s21_owerflow_before_normalization_for_add(s21_decimal value_1,
                                              s21_decimal value_2) {
  int res = 0;

  //check infinity 
  if (value_1.bits[0] == INFINITY || value_1.bits[1] == INFINITY ||
      value_1.bits[2] == INFINITY) {
    if (s21_get_bit(value_1, 127) == 0)
      res = 1;
    else
      res = 2;
  } else if (value_2.bits[0] == INFINITY || value_2.bits[1] == INFINITY ||
             value_2.bits[2] == INFINITY) {
    if (s21_get_bit(value_2, 127) == 0)
      res = 1;
    else
      res = 2;
  }

  //check max unsigned int 
  if (value_1.bits[0] == U_MAX_INT && value_1.bits[1] == U_MAX_INT &&
      value_1.bits[2] == U_MAX_INT && s21_is_zero(value_2) == 1 &&
      s21_get_bit(value_1, 127) == 0 && s21_get_bit(value_2, 127) == 0)
    res = 1;

  else if (value_2.bits[0] == U_MAX_INT && value_2.bits[1] == U_MAX_INT &&
           value_2.bits[2] == U_MAX_INT && s21_is_zero(value_1) == 1 &&
           s21_get_bit(value_2, 127) == 0 && s21_get_bit(value_1, 127) == 0)
    res = 1;

  else if (value_1.bits[0] == U_MAX_INT && value_1.bits[1] == U_MAX_INT &&
           value_1.bits[2] == U_MAX_INT && s21_is_zero(value_2) == 1 &&
           s21_get_bit(value_1, 127) == 1 && s21_get_bit(value_2, 127) == 1)
    res = 2;

  else if (value_2.bits[0] == U_MAX_INT && value_2.bits[1] == U_MAX_INT &&
           value_2.bits[2] == U_MAX_INT && s21_is_zero(value_1) == 1 &&
           s21_get_bit(value_2, 127) == 1 && s21_get_bit(value_1, 127) == 1)
    res = 2;

  return res;
}



/** @brief Checks that the exponenta is not greater that 28
 *
 *
 *  @param value_1 first decimal
 *  @param value_2 second decimal
 *  @return 0 - exponent is correct.  
            1 - exponent exceeded at first decimal.  
            2 - exponent exceeded at second decimal.  
 */
int s21_check_exponenta(s21_decimal value_1, s21_decimal value_2) {
  int res = 0;

  if ((s21_get_exp(value_1) > 28 && s21_get_bit(value_1, 127) == 0) ||
      (s21_get_exp(value_2) > 28 && s21_get_bit(value_2, 127) == 0))
    res = 1;
  else if ((s21_get_exp(value_1) > 28 && s21_get_bit(value_1, 127) == 1) ||
           (s21_get_exp(value_2) > 28 && s21_get_bit(value_2, 127) == 1))
    res = 2;

  return res;
}



/** @brief For number that don't fit into a decimal. Make bank rounding to the lastes digits. (For s21_add())
 *
 *
 *  @param remainder_1 trimmed part of the first decimal
 *  @param remainder_2 trimmed part of the second decimal
 *  @param result rounded decimal
 *  @return 0 - OK.  
            1 - owerflow mantissa  
 */
int s21_banking_round_for_add(int remainder_1[], int remainder_2[],
                              s21_decimal *result) {

  s21_sum_of_ten_array(remainder_1, remainder_2);
  //now the sum of the two trimmed parts into remainder_1

  int last_digit = 0;   //the first digit doesn't fit into the decimal
  for (int i = 29; i >= 0; i--) {
    if (remainder_1[i] != 0) {
      last_digit = remainder_1[i];
      break;
    }
  }

  //if the last_digit is greater that 10, then 1 is transferred to the mast significant digit (last digit in decimal part)
  //Next, we look at the remaining number and use it to make bank rounding

  if (last_digit > 15) {
    if (result->bits[2] == U_MAX_INT && result->bits[1] == U_MAX_INT &&
        result->bits[0] > U_MAX_INT - 2)
      return 1;
    result->bits[0] += 2;
  } else if (last_digit == 15) {
    if (result->bits[0] % 2 == 0) {
      if (result->bits[2] == U_MAX_INT && result->bits[1] == U_MAX_INT &&
          result->bits[0] > U_MAX_INT - 2)
        return 1;
      result->bits[0] += 2;
    } else {
      if (result->bits[2] == U_MAX_INT && result->bits[1] == U_MAX_INT &&
          result->bits[0] > U_MAX_INT - 1)
        return 1;
      result->bits[0] += 1;
    }
  } else if (last_digit > 5) {
    if (result->bits[2] == U_MAX_INT && result->bits[1] == U_MAX_INT &&
        result->bits[0] > U_MAX_INT - 1)
      return 1;
    result->bits[0] += 1;
  } else if (last_digit == 5 && result->bits[0] % 2 == 1) {
    if (result->bits[2] == U_MAX_INT && result->bits[1] == U_MAX_INT &&
        result->bits[0] > U_MAX_INT - 1)
      return 1;
    result->bits[0] += 1;
  }

  return 0;
}



/** @brief For number that don't fit into a decimal. Make bank rounding to the lastes digits. (For s21_sub)
 *
 *
 *  @param remainder_1 trimmed part of the first decimal
 *  @param remainder_2 trimmed part of the second decimal
 *  @param result rounded decimal
 *  @return 0 - OK.  
            1 - owerflow mantissa  
 */
int s21_banking_round_for_sub(int remainder_1[], int remainder_2[],
                              s21_decimal *result) {
  int flag_minus_one = 0;
  if (s21_compare_ten_array(remainder_1, remainder_2) == -1) {
    int position_in_array = 29;
    for (int i = 29; i >= 0; i--) {
      if (remainder_2[i] != 0) {
        position_in_array = i + 1;
        break;
      }
    }
    remainder_1[position_in_array] = 1;
    flag_minus_one = 1;
  }

  s21_sub_of_ten_array(remainder_1, remainder_2);
  //now the sub of the two trimmed parts into remainder_1

  if (flag_minus_one == 1) result->bits[0]--;

  int last_digit = 0;  ////the first digit doesn't fit into the decimal
  for (int i = 29; i >= 0; i--) {
    if (remainder_1[i] != 0) {
      last_digit = remainder_1[i];
      break;
    }
  }

  //look at the remaining number and use it to make bank rounding
  if (last_digit > 5) {
    if (result->bits[2] == U_MAX_INT && result->bits[1] == U_MAX_INT &&
        result->bits[0] > U_MAX_INT - 1)
      return 1;
    result->bits[0] += 1;
  } else if (last_digit == 5 && result->bits[0] % 2 == 1) {
    if (result->bits[2] == U_MAX_INT && result->bits[1] == U_MAX_INT &&
        result->bits[0] > U_MAX_INT - 1)
      return 1;
    result->bits[0] += 1;
  }
  
  return 0;
}