SHELL := /bin/bash
# TODO Make gcov_report target for unit tests reports
DIRS		= ./Functions
# SOURCES 	:= s21_str_test.c
# SOURCES		= $(shell find . -name '*.c')
ODIR 		=./obj
Flags 		= -Werror -Wall -Wextra -std=c11 -fprofile-arcs -ftest-coverage -fPIC
gcc 		= gcc $(Flags)
OS 			:= $(shell uname -s)
clang_path	= ../../materials/build/scripts/
INC			:= $(shell find . -name '*.h')
OBJ 		= $(patsubst %.c,$(ODIR)/%.o, $(SOURCES))
TEST_O		= $(ODIR)/s21_str_test.o

$(ODIR)/%.o: %.c $(INC)
	$(gcc) $< -c -o $@
all: clear clean s21_string.a test
clear:
	clear
clean:
	rm -rf s21_string.a test *.out $(ODIR)/*.o $(ODIR)/*.gcda $(ODIR)/*.gcno *.gcov
	cd ./Functions; make clean
obj: $(OBJ)
	cd ./Functions; make
clang:
	clang-format --style=Google -n ./*.c ./*.h ./Functions/*.c
clang-replace:
	clang-format --style=Google -i *.c *.h ./Functions/*.c
s21_string.a: obj
	ar rcs $@ $(ODIR)/Functions/*.o
test: s21_string.a $(TEST_O)
	$(gcc) $^ -o $@ `pkg-config --cflags --libs check`
gcov_report: test
	./test
	gcov $(ODIR)/s21_str_test.c
.PHONY: clean obj clear s21_string test clang-replace all