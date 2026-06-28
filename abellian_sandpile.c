#include <asm-generic/ioctls.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>

#define CLEAR_GRID "\033[0m"
#define COLOR_RED "\033[31m"    // cell value 4
#define COLOR_ORANGE "\033[31m" // cell value 3
#define COLOR_YELLOW "\033[31m" // cell value 2
#define COLOR_WHITE "\033[31m"  // cell value 1

#define WIDTH 40
#define HEIGHT 40

int init_grid(int positions[HEIGHT][WIDTH]);
int draw_new_positions();
int render();

int main() {
  // gets terminal window size
  struct winsize w;
  // ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

  int positions[HEIGHT][WIDTH];
  int (*ppositions)[] = positions;
  int new_positions[HEIGHT][WIDTH];

  printf("starting abellian sandpile simulation\n");
  init_grid(ppositions);
  printf("\ninitialized grid");
  return 0;
}

int init_grid(int positions[HEIGHT][WIDTH]) {
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      positions[i][j] = 0;
      printf("%d", positions);
    }
    printf("\n");
  }

  return 0;
}
