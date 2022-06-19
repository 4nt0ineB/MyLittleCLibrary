# Compilation settings
CC = gcc
CFLAGS = -ansi -pedantic -Wall -O2 -g
LDFLAGS =

# define working directories
SRC_DIR = src
HEADERS_DIR= include
OUT_DIR = bin
OBJ_DIR = $(OUT_DIR)/obj

LIB_NAME = libMLCL
LIB_PATH = ${OUT_DIR}/${LIB_NAME}

# Extract files path
SRC = $(shell find $(SRC_DIR)/ -name \*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
DEP = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.d, $(SRC))

# default target : create installation dir, make the lib, create its index
all: --make_install_dir $(LIB_PATH) index

# make the lib and run tests
test: all
	gcc test.c -o ./$(OUT_DIR)/MLCLTests -L. -lMLCL
	./$(OUT_DIR)/MLCLTests

valtest: all
	gcc test.c -o ./$(OUT_DIR)/MLCLTests -L. -lMLCL
	valgrind --track-origins=yes --leak-check=full -s ./$(OUT_DIR)/MLCLTests

$(LIB_PATH): $(OBJ)
	ar r $(LIB_NAME).a $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -MMD -MP -c $< -o $@ $(CFLAGS)

index: $(LIB_PATH)
	ranlib $(LIB_NAME).a

# to see lib index
# nm -s libMLCL.a

-include $(DEP)

--make_install_dir:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(shell dirname $(OBJ))

.PHONY: clean
clean:
	@rm -rf $(OBJ_DIR)

mrproper: clean
	rm -f $(LIB_NAME).a
	rm -f $(OUT_DIR)/MLCLTests
	rmdir $(OUT_DIR)

