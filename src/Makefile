SHELL := /bin/bash
# TODO Compile project as static liblary
DIRS		= ./Functions
# SOURCES 	:= s21_str_test.c
# SOURCES		+= $(shell find $(DIRS) -name '*.h')
ODIR 		=./obj
Flags 		= -Werror -Wall -Wextra -std=c11 -g
gcc 		= gcc $(Flags)
OS 			:= $(shell uname -s)
clang_path	= ../../materials/build/scripts/
INC			:= $(shell find . -name '*.h')
OBJ 		= 	$(patsubst %.c,$(ODIR)/%.o, $(SOURCES))
$(ODIR)/%.o: %.c $(INC)
	$(gcc) $< -c -o $@
all: clear s21_string
clear:
	clear
clean:
	rm -rf s21_string test *.out $(ODIR)/*.o
	cd ./Functions; make clean
obj: $(OBJ)
	cd ./Functions; make
clang:
	clang-format --style=Google -n *.c *.h ./*/*.c ./*/*.h
clang-replace:
	clang-format --style=Google -i *.c *.h ./*/*.c ./*/*.h
main:
	rm -rf $(ODIR)/s21_str_test.o
	make s21_string
s21_string: obj $(ODIR)/main.o
	$(gcc) $(ODIR)/*.o $(ODIR)/Functions/*.o -o $@
.PHONY: clean obj clear s21_string
test: obj $(ODIR)/s21_str_test.o
	rm -rf $(ODIR)/main.o
	$(gcc) -lcheck $(ODIR)/*.o $(ODIR)/Functions/*.o -o $@