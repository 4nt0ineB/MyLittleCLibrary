# Compilation settings
CC = gcc
CFLAGS = -ansi -pedantic -Wall -O2 -g
LDFLAGS =

# def working dirs
SRC_DIR = src
HEADERS_DIR= include
OUT_DIR = bin
OBJ_DIR = $(OUT_DIR)/obj

LIB_NAME = libMLCL
LIB_PATH = ${OUT_DIR}/${LIB_NAME}
args =

# Extract files path
SRC = $(shell find $(SRC_DIR)/ -name \*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
DEP = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.d, $(SRC))

# defaut target : create installation dir, make the lib, create its index
all: --make_install_dir $(LIB_PATH) index

$(LIB_PATH): $(OBJ)
	ar r $(LIB_NAME).a $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -MMD -MP -c $< -o $@ $(CFLAGS)

index: $(LIB_PATH).a
	ranlib $(LIB_PATH).a

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
	@rm -f $(LIB_PATH).a

test: all
	gcc test.c -o ./$(OUT_DIR)/MLCLTests -L.  -lMLCL
	./$(OUT_DIR)/MLCLTests