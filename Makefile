CC = gcc
CFLAGS = -I.

all: banker

banker: banker.c
	$(CC) -o banker banker.c $(CFLAGS)

clean:
	rm banker
