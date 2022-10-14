# Compilation settings
CC = gcc
CFLAGS = -ansi -pedantic -Wall -O2
LDFLAGS = -LMLCL -lMLCL

# define working directories
SRC_DIR = src/
HEADERS_DIR = include
OUT_DIR = bin
OBJ_DIR = $(OUT_DIR)/obj
OBJ = Main.o Person.o Movie.o
OBJ:= $(addprefix $(SRC_DIR), $(OBJ))

EXE=mlcl_example

run: $(EXE)
	./$(EXE)

$(EXE):	$(OBJ)
	$(CC) -o $@ $(notdir $^) $(CFLAGS) $(LDFLAGS)
	
%.o: %.c
	$(CC) -c $< $(CFLAGS)

Main.o: Main.c include/Person.h include/Movie.h
Person.o: src/Person.c include/Person.h
Movie.o: src/Movie.c include/Movie.h include/Person.h

.PHONY: clean mrproper

clean:
	rm -f *.o $(EXE)