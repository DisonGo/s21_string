DIRS		= ./Functions
SOURCES		= $(shell find . -name '*.c')
REPORTS		= $(shell find . -name '*.gcno') $(shell find . -name '*.gcda')
ODIR 		=./obj
Flags 		= -Werror -Wall -Wextra -std=c11
gcc 		= gcc $(Flags)
OS 			:= $(shell uname -s)
clang_path	= ../../materials/build/scripts/
INC			:= $(shell find . -name '*.h')
OBJ 		= $(patsubst %.c,$(ODIR)/%.o, $(SOURCES))
TEST_O		= $(ODIR)/s21_str_test.o

$(ODIR)/%.o: %.c $(INC)
	$(gcc) $< -c -o $@
all: clear clean test
clear:
	clear
clean:
	rm -rf s21_string.a test *.out $(ODIR)/*.o $(ODIR)/*.gcno $(ODIR)/*.gcda ./gcov/*.gcno ./gcov/*.gcda  ./gcov/*.gcov
obj: $(OBJ)
clang:
	clang-format --style=Google -n ./*.c ./*.h ./Functions/*.c
clang-replace:
	clang-format --style=Google -i *.c *.h ./Functions/*.c
s21_string.a: obj
	ar rcs $@ $(ODIR)/Functions/*.o
set_debug_gcc:
	$(eval gcc += -g)
	@echo Debug build
set_check_gcc:
	$(eval gcc += -fprofile-arcs -ftest-coverage -fPIC)
	@echo Check build
test: set_check_gcc s21_string.a $(TEST_O)
	$(gcc) s21_string.a $(TEST_O) -o $@ `pkg-config --cflags --libs check`
gcov_report: clean test
	./test
	gcov *.c ./Functions/*.c -o $(ODIR)/*
	mv *.gcov ./gcov
	mv $(ODIR)/*.gcda $(ODIR)/*.gcno $(ODIR)/*/*.gcda $(ODIR)/*/*.gcno ./gcov
	$(brsw)
	lcov -t ./gcov -o report.info -c -d ./gcov
	genhtml -o report report.info

.PHONY: clean obj clear s21_string test clang-replace all s21_string.a set_debug_gcc set_check_gcc gcov_report