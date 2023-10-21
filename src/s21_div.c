#include "s21_decimal.h"


/** @brief Divide two decimal, the result of the addition is writen into result
 *
 *
 *  @param value_1 dividend
 *  @param value_2 divisor
 *  @param result quotient
 *  @return 0 - OK.  
            1 - the number is too large or equal to infinity.  
            2 - the number is too small or equal to negative infinity.
            3 - divide by 0.
 */
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int res = 0;

  int error = 0;
  error = s21_is_owerflow_decimal(value_1);
  if (error != 0 && s21_get_bit(value_1, 127) == 1) return 2;
  if (error != 0 && s21_get_bit(value_1, 127) == 0) return 1;
  error = s21_is_owerflow_decimal(value_2);
  if (error != 0 && s21_get_bit(value_2, 127) == 1) return 2;
  if (error != 0 && s21_get_bit(value_2, 127) == 0) return 1;
  error = s21_check_exponenta(value_1, value_2);
  if (error != 0) return 2;

  //checking if value_2 is not a zero
  if (s21_is_zero(value_2) == 0) return 3;

  //if value_1 is zero, result is zero too
  if (s21_is_zero(value_1) == 0) {
    result->bits[0] = 0;
    result->bits[1] = 0;
    result->bits[2] = 0;
    result->bits[3] = 0;
  }

  //find the sign of the result (0 - plus, 1 - minus)
  int sign = 0;
  if ((s21_get_bit(value_1, 127) == 1 && s21_get_bit(value_2, 127) == 0) ||
      (s21_get_bit(value_1, 127) == 0 && s21_get_bit(value_2, 127) == 1))
    sign = 1;

  //convert all into big_decimal and big_ten_array 
  s21_big_decimal big_value_1 = {0};
  s21_big_decimal big_value_2 = {0};
  s21_cpy_decimal_to_big_decimal(value_1, &big_value_1);
  s21_cpy_decimal_to_big_decimal(value_2, &big_value_2);

  int big_ten_array_1[90] = {0};
  int big_ten_array_2[90] = {0};
  s21_from_big_decimal_to_ten_array(big_value_1, big_ten_array_1);
  s21_from_big_decimal_to_ten_array(big_value_2, big_ten_array_2);
  int big_ten_array_result[90] = {0};

  //We need to remove the exponents and turn both numbers into "integers".
  //To do this, we find the difference between the exponents and multiply the number
  //with the smaller exponent by 10 the same number of times, 
  //and both exponents become equal to zero
  int exp_1 = s21_get_exp(value_1);
  int exp_2 = s21_get_exp(value_2);
  int diff_exp = exp_1 - exp_2;
  //the first has a larger exponent, so we move the second
  if (diff_exp > 0) {
    for (int i = 0; i < diff_exp; i++)
      s21_mul_ten_big_ten_array(big_ten_array_2);
  }
  //the second has a larger exponent, so we move the first
  else if (diff_exp < 0) {
    for (int i = 0; i < -diff_exp; i++)
      s21_mul_ten_big_ten_array(big_ten_array_1);
  }

  //непосредственно деление мантисс (алгоритм как у обычного деления в столбик)
  int exp_rezult = s21_div_big_ten_array(big_ten_array_1, big_ten_array_2,
                                         big_ten_array_result);

  //проверяем мантиссу на переполнение
  int flag_owerflow_mantisa = s21_is_owerflow_mantissa_for_big_ten_array(
      exp_rezult, big_ten_array_result);

  int remainder = 0;  //запоминает последнюю усеченную цифру (для последующего округления)
  int max_ten_array[] = {5, 3, 3, 0, 5, 9, 3, 4, 5, 3, 9, 5, 7, 3, 3,
                         4, 6, 2, 4, 1, 5, 2, 6, 1, 8, 2, 2, 9, 7, 0};
  if (flag_owerflow_mantisa == 0) {
    int max_big_ten_array[90] = {0};
    for (int i = 0; i < 30; i++) max_big_ten_array[i] = max_ten_array[i];

    //пока наш большой десятичный массив больше максимально возможного, отрезаем
    //числа после запятой плюс запоминаем последнее усеченное число, чтобы потом
    //применить банковское округление
    while (s21_compare_big_ten_array(big_ten_array_result, max_big_ten_array) ==
               1 ||
           exp_rezult > 28) {
      exp_rezult--;
      remainder = big_ten_array_result[0];
      for (int j = 0; j < 89; j++)
        big_ten_array_result[j] = big_ten_array_result[j + 1];
      big_ten_array_result[89] = 0;
    }
  } else {
    if (sign == 0)
      res = 1;
    else
      res = 2;
  }

  //применяем банковское округление
  s21_banking_round_for_mult(big_ten_array_result, remainder);

  //переводим результат обратно в биг децимал
  s21_big_decimal copy = {0};
  s21_from_ten_array_to_big_decimal(big_ten_array_result, &copy);

  //превращаем биг децимал в обычный децимал
  for (int i = 0; i < 3; i++) result->bits[i] = copy.bits[i];
  s21_set_bit_V2(result, 127, sign);
  s21_set_exp(*result, result, exp_rezult);

  return res;
}

//делит два больших десятичных массива, алгоритм похож на обычное деление в
//столбик ручками в качестве результата возвращает количество цифр в мантиссе
int s21_div_big_ten_array(int value_1[], int value_2[], int result[]) {
  int exp_result = 0;

  int counter = 0;  //индекс первого числа (самого старшеразрядного) в value_1,
                    //чтобы друг под другом разместить
  //далее это индекс той цифры в value_1, которую сносим вниз
  int a[90] = {0};  //уменьшаемое на каждом шаге
  int b[90] = {0};  //вычитаемое на каждом шаге
  // int quotient = 0; //частное на каждом шаге
  int size_of_ab = 0;  //количество значимых цифр при пошаговом вычитании
  int count_result =
      0;  //просто счетчик инжекса для записывания в reverse_result
  int reverse_result[90] = {0};  //перевернулый результат

  //находим first_digit (индекс первого числа в массиве)
  for (int i = 89; i >= 0; i--) {
    if (value_1[i] != 0) {
      counter = i;
      break;
    }
  }

  //находим size_of_ab
  for (int i = 89; i >= 0; i--) {
    if (value_2[i] != 0) {
      size_of_ab = i + 1;
      break;
    }
  }

  //     //изначально b это и есть value_2

  if (size_of_ab > counter + 1) size_of_ab = counter + 1;
  //определяем изначальное а (переписываем первые size_of_ab цифр из value_1)
  for (int i = 0; i < size_of_ab; i++) {
    a[i] = value_1[counter - size_of_ab + 1 + i];
  }
  counter = counter - size_of_ab + 1;  // 7 - 3 + 1 = 5

  while (s21_is_zero_array_for_big_decimal(a) == 0 || counter != 0) {

    //изначально b это и есть value_2
    for (int i = 0; i < 89; i++) b[i] = value_2[i];

    int quotient = 1;  //частное на каждом шаге

    int counter_of_null = 0;
    //если а меньше b, то в а сносим ещё одну цифру   
    if (s21_compare_big_ten_array(a, b) == -1) {
      //если дошли до конца и больше сносить нечего, то сносим 0, а
      //результирующую экспоненту увеличивает на 1
      if (counter == 0) {
        s21_mul_ten_big_ten_array(a);
        exp_result++;

        if (a[0] == 0)
          counter_of_null++;
        else
          counter_of_null = 0;
      }
      //если есть, что сносить, то сносим цифру под индексом counter-1, сам
      // counter сдвигаем дальше
      else {
        s21_mul_ten_big_ten_array(a);
        counter--;
        a[0] = value_1[counter];

        if (a[0] == 0)
          counter_of_null++;
        else
          counter_of_null = 0;
      }
    }

    while (s21_compare_big_ten_array(a, b) == -1) {

      quotient = 1;
      //если дошли до конца и больше сносить нечего, то сносим 0, а
      //результирующую экспоненту увеличивает на 1
      if (counter == 0) {
 
        for (int i = 0; i < counter_of_null; i++) {
          reverse_result[count_result] = 0;
          count_result++;
        }
        break;

        s21_mul_ten_big_ten_array(a);
      }
      //если есть, что сносить, то сносим цифру под индексом counter-1, сам
      // counter сдвигаем дальше
      else {
        s21_mul_ten_big_ten_array(a);
        counter--;
        a[0] = value_1[counter];

        if (a[0] == 0)
          counter_of_null++;
        else
          counter_of_null = 0;
      }
    }

    //к b прибавляем value_2 до тех пор, пока b не станет максимально возможным,
    //но все еще меньше a
    while (s21_compare_big_ten_array(a, b) == 1) {
      s21_sum_of_ten_array_for_big_decimal(b, value_2);
      quotient++;
    }
    //если перестарались и теперь b стало больше a, вычитаем один value_2 из b
    //обратно
    if (s21_compare_big_ten_array(a, b) == -1) {
      s21_sub_of_big_ten_array(b, value_2);
      quotient--;
    }

    //записываем quotient в результат
    if (quotient != 0) {
      reverse_result[count_result] = quotient;
      count_result++;
    }


    //вычитаем b из а, теперь а это результат вычитания
    s21_sub_of_big_ten_array(a, b);

    if (count_result == 90) break;
  }

  //перенесем из revers_result в нормальный result (но следим за количеством
  //записанных чисел)
  int count_tmp = 0;
  for (int i = count_result - 1; i >= 0; i--) {
    result[count_tmp] = reverse_result[i];
    count_tmp++;
  }

  if (exp_result > 89) exp_result = 89;

  return exp_result;
}

//просто умножает большой десятичный массив на 10 (без обработки каких-либо
//ошибок)
void s21_mul_ten_big_ten_array(int value[]) {
  for (int j = 89; j > 0; j--) value[j] = value[j - 1];
  value[0] = 0;
}