#include <ncurses.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define COLOR_DARK_BLUE "\033[38;5;19m"	 // cell value 4 (Dark Blue)
#define COLOR_MED_BLUE "\033[38;5;33m"	 // cell value 3 (Medium Blue)
#define COLOR_LIGHT_BLUE "\033[38;5;81m" // cell value 2 (Light Blue)
#define COLOR_ICE_BLUE "\033[38;5;195m"	 // cell value 1 (Very Light Blue)

struct sandpile {
	size_t rows;
	size_t columns;
	size_t *cells;
	size_t *next;
	bool paused;
	size_t steps;
};

static void init_sandpile(struct sandpile *sandpile);
static void destroy_sandpile(struct sandpile *sandpile);

static void add_grain(struct sandpile *sandpile);
static void update_sandpile(struct sandpile *sandpile);

static void draw_sandpile(struct sandpile *sandpile);
static void draw_status(struct sandpile *sandpile);

static bool handle_input(struct sandpile *sandpile);

int main(void)
{
	struct sandpile sandpile;

	if (initscr() == NULL) {
		fprintf(stderr, "Failed to init ncurses screen");
	}

	if (has_colors()) {
		start_color();
		use_default_colors();

		// colors
		init_pair(1, COLOR_GREEN, COLOR_BLACK);
		init_pair(2, COLOR_YELLOW, COLOR_BLACK);
		init_pair(3, COLOR_CYAN, COLOR_BLACK);
		init_pair(4, COLOR_WHITE, COLOR_BLACK);
	}

	cbreak();
	noecho();
	keypad(stdscr, true);
	nodelay(stdscr, true);
	curs_set(0);

	init_sandpile(&sandpile);

	bool running = true;
	while (running) {
		if (!sandpile.paused) {
			add_grain(&sandpile);
			update_sandpile(&sandpile);
			draw_sandpile(&sandpile);
		}
		running = handle_input(&sandpile);
	}

	destroy_sandpile(&sandpile);
	endwin();

	return 0;
}

static void init_sandpile(struct sandpile *sandpile)
{
	// gets screen dimensions
	getmaxyx(stdscr, sandpile->rows, sandpile->columns);
	sandpile->rows -= 1;
	sandpile->columns /= 2;

	sandpile->cells =
	    calloc(sandpile->rows * sandpile->columns, sizeof(size_t));
	sandpile->next =
	    calloc(sandpile->rows * sandpile->columns, sizeof(size_t));

	sandpile->paused = false;
	sandpile->steps = 0;

	erase();
}

static void destroy_sandpile(struct sandpile *sandpile)
{
	free(sandpile->cells);
	free(sandpile->next);
}

static void add_grain(struct sandpile *sandpile)
{
	sandpile->cells[(sandpile->rows / 2) * sandpile->columns +
			(sandpile->columns / 2)] += 1;
}

static void update_sandpile(struct sandpile *sandpile)
{
	// clear next to all 0s
	memset(sandpile->next, 0,
	       sandpile->rows * sandpile->columns * sizeof(size_t));

	// calculating new positions
	for (size_t row = 0; row < sandpile->rows; row++) {
		for (size_t column = 0; column < sandpile->columns; column++) {
			size_t value =
			    sandpile->cells[row * sandpile->columns + column];
			size_t topples = value / 4;

			sandpile->next[row * sandpile->columns + column] +=
			    value % 4;

			if (column > 0) {
				sandpile->next[row * sandpile->columns +
					       column - 1] += topples;
			}
			if (column + 1 < sandpile->columns) {
				sandpile->next[row * sandpile->columns +
					       column + 1] += topples;
			}
			if (row > 0) {
				sandpile->next[(row - 1) * sandpile->columns +
					       column] += topples;
			}
			if (row + 1 < sandpile->rows) {
				sandpile->next[(row + 1) * sandpile->columns +
					       column] += topples;
			}
		}
	}

	size_t *tmp = sandpile->cells;
	sandpile->cells = sandpile->next;
	sandpile->next = tmp;

	sandpile->steps++;
}

static void draw_status(struct sandpile *sandpile)
{

	char status[256];
	snprintf(status, sizeof(status), "STEP: %zu %s", sandpile->steps,
		 sandpile->paused ? "PAUSED" : "RUNNING");

	attron(A_REVERSE);
	move(0, 0);
	mvaddnstr(0, 0, status, sandpile->columns);
	for (int column = (int)strlen(status); column < sandpile->columns * 2;
	     column++) {
		mvaddch(0, column, ' ');
	}
	attroff(A_REVERSE);
}

static void draw_sandpile(struct sandpile *sandpile)
{
	char pixel;
	size_t color_pair = 0;
	bool is_bold = false;

	for (size_t row = 0; row < sandpile->rows; row++) {
		for (size_t column = 0; column < sandpile->columns; column++) {
			// grab pixel value from array
			size_t value =
			    sandpile->cells[row * sandpile->columns + column];

			// set color and ASCII character
			if (value == 0) {
				color_pair = 4;
				pixel = ' ';
			} else if (value == 1) {
				color_pair = 4;
				pixel = '.';
				is_bold = false;
			} else if (value == 2) {
				color_pair = 3;
				pixel = ':';
				is_bold = false;
			} else if (value == 3) {
				color_pair = 2;
				pixel = '#';
				is_bold = true;
			} else {
				color_pair = 1;
				pixel = '@';
				is_bold = true;
			}

			if (color_pair > 0) {
				attron(COLOR_PAIR(color_pair));
				if (is_bold) {
					attron(A_BOLD);
				}
			}

			mvaddch(row + 1, column * 2, pixel);
			mvaddch(row + 1, column * 2 + 1, pixel);

			if (color_pair > 0) {
				attroff(COLOR_PAIR(color_pair));
				if (is_bold) {
					attroff(A_BOLD);
				}
			}
		}
	}

	draw_status(sandpile);
	refresh();
}

static bool handle_input(struct sandpile *sandpile)
{

	int key = getch();

	switch (key) {
	case 'q':
	case 'Q':
		return false;

	case ' ':
	case 'p':
	case 'P':
		sandpile->paused = !sandpile->paused;
		break;

		// case 'r':
		// case 'R':
		// 	destroy_sandpile(sandpile);
		// 	break;

	default:
		break;
	}

	return true;
}
