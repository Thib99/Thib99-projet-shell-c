CC = gcc
OPTION_COMPIL = -g
REP_CODE = code
EXEC = projet

# variable auto-rempli
OSFLAG :=
SRC = $(wildcard $(REP_CODE)/*.c)
OBJ = $(SRC:.c=.o)

all : $(EXEC)

o%. :%.c
	$(CC) $(OPTION_COMPIL) -o $@ -c $<

$(EXEC) : $(OBJ)
	$(CC) $(OPTION_COMPIL) -o $@ $^

clean :
ifeq ($(OS), Windows_NT)
	del -f  $(EXEC).exe $(EXEC) $(REP_CODE)\*.o
else
	rm -f  $(EXEC).exe $(EXEC) $(REP_CODE)/*.o
endif

run :
ifeq ($(OS), Windows_NT)
	cls
	make all
	./$(EXEC).exe
else
	clear
	make all
	./$(EXEC)
endif

vg :
	make all
	clear
	valgrind -s --leak-check=full --show-leak-kinds=all ./$(EXEC)