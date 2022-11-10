SHELL := /bin/bash

DIRS		= ./Functions
SOURCES 	:= main.c
# SOURCES		+= $(shell find $(DIRS) -name '*.h')
ODIR 		=./obj
Flags 		= -Werror -Wall -Wextra -std=c11
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
	rm -rf s21_string *.out $(ODIR)/*.o
	cd ./Functions; make clean
obj: $(OBJ)
	cd ./Functions; make
s21_string: obj
	$(gcc) $(ODIR)/*.o $(ODIR)/Functions/*.o -o $@
.PHONY: clean obj clear s21_string