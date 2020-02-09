CC = gcc
CFLAGS = -std=c99 -Wall -fsanitize=address,undefined -fno-sanitize-recover=all -fsanitize-undefined-trap-on-error

SRC = main.c
OBJ = $(SRC:.c=.o)

TEST_SRC = test.c
TEST_OBJ = $(TEST_SRC:.c=.o)

FOLDERS = fs
FOLDER_FILES = $(foreach item,$(FOLDERS),$(item)/$(item).o)

all: options folders
	$(CC) -c $(CFLAGS) $(SRC)
	$(CC) $(CFLAGS) $(OBJ) $(FOLDER_FILES) -o nn -lm

.ONESHELL:
folders:
	for folder in $(FOLDERS); do $(MAKE) -C "$$folder"; done

test: options folders
	@echo "==============================================================================="
	$(CC) -c $(CFLAGS) $(TEST_SRC)
	$(CC) $(CFLAGS) $(TEST_OBJ) $(FOLDER_FILES) -o test -lm
	@echo "==============================================================================="
	./test

options:
	@echo profile build options:
	@echo "CC       = $(CC)"
	@echo "CFLAGS   = $(CFLAGS)"

.c.o:
	$(CC) -c $(CFLAGS) $<

clean:
	rm *.o
