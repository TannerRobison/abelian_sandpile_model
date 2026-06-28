CC = gcc
Cflags = -I.

abellian_sandpile:
	$(CC) -o abellian_sandpile abellian_sandpile.c

clean:
	rm -f abellian_sandpile
