CC = gcc
CFLAGS = -g -Wall -Werror -Wextra -std=c11
FLAG_C = -c
LFLAGS = -Wall -Werror -Wextra -g -fsanitize=leak -fsanitize=address -fsanitize=undefined -fsanitize=unreachable -fno-sanitize-recover -fstack-protector -fanalyzer
COVFLAGS = -fprofile-arcs -ftest-coverage
TESTFALGS = -lcheck
ifeq ($(shell uname), Linux)
	TESTFALGS += -lpthread -lrt -lsubunit -lm
endif
FILES = s21_*.c
TEST_FILES = suite_*.c main.c
s21_decimal_O = s21_*.o

all: clean test

s21_decimal.a:
	$(CC) $(FLAG_C) $(CFLAGS) $(FILES)
	ar rc s21_decimal.a $(s21_decimal_O)
	ranlib s21_decimal.a


test: s21_decimal.a
	$(CC) $(CFLAGS) $(TEST_FILES) s21_decimal.a $(TESTFALGS) -o test_rez
	./test_rez

gcov_report:
	$(CC) $(CFLAGS) $(TEST_FILES) $(TESTFALGS) $(COVFLAGS) $(FILES) -o test_rez
	./test_rez
	lcov -t "Decimal_tests" -o test_rez.info -c -d .
	genhtml -o report test_rez.info
	rm *.gcda *.gcno *.info
	open report/index.html

style:
	clang-format -i --style=Google *.c *.h

clean:
	rm -rf report test_rez *.a *.o

leaks: s21_decimal.a
	clear
	$(CC) $(CFLAGS) $(TEST_FILES) s21_decimal.a
	valgrind --tool=memcheck --leak-check=yes  ./a.out
	leaks -atExit -- ./a.out
	$(CC) $(LFLAGS) $(TEST_FILES) s21_decimal.a -o 1
	./1

.PHONY: all, test, gcov_report, style, clean, s21_decimal.a


