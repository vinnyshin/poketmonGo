CROSS=
CC=$(CROSS)gcc
EXE=run
DEFINES=#-DDEBUG
CFLAGS= -I./include $(DEFINES)
LDFLAGS= -lpthread

C_SRC = $(wildcard *.c)
OBJ = $(C_SRC:.c=.o)


all : $(EXE)
	echo completed!!!!
$(EXE) : $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)


clean :
	rm *.o
	rm run

good :
	echo good
