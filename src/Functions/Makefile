Flags 		= -Werror -Wall -Wextra -std=c11
gcc 		= gcc $(Flags)
ODIR 		=../obj/Functions
SOURCES 	:= $(shell find . -name '*.c')
OBJ 		= 	$(patsubst ./%.c,$(ODIR)/%.o, $(SOURCES))
all: obj

$(ODIR)/%.o: %.c $(INC)
	$(gcc) -g $< -c -o $@
obj: $(OBJ)
clean:
	rm -rf $(ODIR)/*.o