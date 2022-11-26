SOURCES		= $(shell find ./Functions -name '*.c')
REPORTS		= $(shell find . -name '*.gcno') $(shell find . -name '*.gcda')
ODIR 		=./obj
Flags 		= -Werror -Wall -Wextra -std=c11
gcc 		= gcc $(Flags)
INC			:= $(shell find . -name '*.h')
OBJ 		= $(patsubst %.c,$(ODIR)/%.o, $(SOURCES))
TEST_O		= $(ODIR)/s21_str_test.o
UNAME_S 	:=$(shell uname -s)

ifeq ($(UNAME_S),Linux)
	TEST_CHECK_F= -lcheck
	OPEN_CMD = xdg-open
	ADD_LIB = -lm -lrt -lpthread
endif
ifeq ($(UNAME_S),Darwin)
	TEST_CHECK_F= $(shell pkg-config --cflags --libs check)
	OPEN_CMD = open
	ADD_LIB =
endif
$(ODIR)/%.o: %.c $(INC)
	$(gcc) $(ADD_LIB) $< -c -o $@
all: clear s21_string.a
clear:
	clear
clean:
	rm -rf s21_string.a test *.out
	rm -rf $(ODIR)/*.o $(ODIR)/*.gcno $(ODIR)/*.gcda
	rm -rf $(ODIR)/*/*.o $(ODIR)/*/*.gcno $(ODIR)/*/*.gcda
	rm -rf ./gcov/*.o ./gcov/*.gcno ./gcov/*.gcda ./gcov/*.gcov
	rm -rf report*
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
set_report_gcc:
	$(eval gcc += -fprofile-arcs -ftest-coverage -fPIC)
	@echo Check build
test: s21_str_test.c s21_string.a
	$(gcc) $^ -o $@ $(TEST_CHECK_F) $(ADD_LIB)
gcov_report: clean set_report_gcc test
	./test
	gcov *.c ./Functions/*.c -o $(ODIR)/*
	mv *.gcov ./gcov
	mv ./*.gcda ./*.gcno $(ODIR)/*/*.gcda $(ODIR)/*/*.gcno ./gcov
	lcov -t ./gcov -o report.info -c -d ./gcov
	genhtml -o report report.info
	$(OPEN_CMD) ./report/index.html
.PHONY: clean obj clear s21_string test clang-replace all s21_string.a set_debug_gcc set_report_gcc gcov_report