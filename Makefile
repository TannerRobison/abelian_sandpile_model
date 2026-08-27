CC=clang
CFLAGS=-Wall -Wextra -Wpedantic
NCURSES=$(shell pkg-config --cflags --libs ncursesw)

abellian_sandpile: abellian_sandpile.c
	$(CC) $(CFLAGS) abellian_sandpile.c -o abellian_sandpile $(NCURSES)

run: abellian_sandpile
	./abellian_sandpile

clean:
	rm -f abellian_sandpile

.PHONY: run clean
