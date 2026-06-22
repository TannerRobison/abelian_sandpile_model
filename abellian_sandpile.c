#include <asm-generic/ioctls.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>

#define CLEAR_GRID "\033[0m"
#define COLOR_RED "\033[31m"    // cell value 4
#define COLOR_ORANGE "\033[31m" // cell value 3
#define COLOR_YELLOW "\033[31m" // cell value 2
#define COLOR_WHITE "\033[31m"  // cell value 1

int positions[HEIGHT][WIDTH];
int new_positions[HEIGHT][WIDTH];

int

    void
    init_grid();
void draw_new_positions();
void render();

int main() {
  // gets terminal window size
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

  printf("starting abellian sandpile simulation\n");
  init_grid();
  printf("\ninitialized grid");
  return 0;
}

void init_grid() {
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      printf(" ");

      // prints a X around the borders
      if (j = (WIDTH - 1)) {
        printf("|");
      }
    }
  }
}
