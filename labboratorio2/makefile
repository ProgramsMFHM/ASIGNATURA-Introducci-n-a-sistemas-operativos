CC=gcc
SRC_DIR=src
OBJ_DIR=obj
BUILD_DIR=build
SRC_FILES=$(wildcard $(SRC_DIR)/*.c)
OBJ_FILES=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))
PROG_FILES=$(filter-out $(BUILD_DIR)/%.no_main.out,$(patsubst $(OBJ_DIR)/%.o,$(BUILD_DIR)/%.out,$(OBJ_FILES)))
INCLUDE=-I./incs/
LIBS= -lm

CFLAGS=-Wall -Wextra -Wpedantic -O3
LDFLAGS= -Wall -lm

all: $(PROG_FILES)

$(BUILD_DIR)/%.out: $(OBJ_DIR)/%.o $(OBJ_DIR)/complex.o
	@if grep -q "int main" $(patsubst $(BUILD_DIR)/%.out,$(SRC_DIR)/%.c,$@); then \
		echo "Compiling executable $@"; \
		$(CC) $(CFLAGS) $^ -o $@ $(LIBS); \
	else \
		echo "Skipping executable for $@ (no main function)"; \
		rm -f $@; \
	fi

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $^ $(INCLUDE) $(LIBS)

.PHONY: clean folders
clean:
	rm -f $(OBJ_FILES)
	rm -f build/*

folders:
	mkdir -p src obj incs build docs