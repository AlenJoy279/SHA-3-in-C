CC = gcc
CFLAGS = -I. -I./externals/keccak -Wall -g
LDFLAGS =

KECCAK_DIR = ./externals/keccak
KECCAK_SRC = $(wildcard $(KECCAK_DIR)/*.c)
KECCAK_OBJ = $(filter-out $(KECCAK_DIR)/main.o, $(KECCAK_SRC:.c=.o))

# Exclude main.c from being compiled with tests
SHA_SRC = $(wildcard *.c)
SHA_OBJ = $(SHA_SRC:.c=.o)

TESTS_DIR = ./tests
TESTS_SRC = $(wildcard $(TESTS_DIR)/*.c)
TESTS_OBJ = $(TESTS_SRC:.c=.o)

# Main target to build all tests
all: test_exec

$(KECCAK_DIR)/%.o: $(KECCAK_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TESTS_DIR)/%.o: $(TESTS_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

test_exec: $(KECCAK_OBJ) $(SHA_OBJ) $(TESTS_OBJ)
	$(CC) $(LDFLAGS) $(KECCAK_OBJ) $(SHA_OBJ) $(TESTS_OBJ) -o $@

clean:
	rm -f *.o $(KECCAK_DIR)/*.o $(TESTS_DIR)/*.o test_exec

.PHONY: all clean test_exec
