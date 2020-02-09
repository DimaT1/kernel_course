CC = gcc
LD = ld

CFLAGS = -std=c99 -Wall -fsanitize=address,undefined -fno-sanitize-recover=all -fsanitize-undefined-trap-on-error

SRC = disk.c superblock.c
OBJ = $(SRC:.c=.o)

all:
	$(CC) $(CFLAGS) $(SRC) -c
	$(LD) -relocatable $(OBJ) -o fs.o

clean:
	rm *.o
