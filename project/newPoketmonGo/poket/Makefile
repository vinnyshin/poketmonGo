CROSS=
CC=$(CROSS)gcc
EXE=poket
DEFINES=#-DFILE_MODE
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
	rm $(EXE)

good :
	echo good
