#include <asm-generic/ioctls.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define CLEAR_GRID "\033[0m"
#define COLOR_RED "\033[31m"    // cell value 4
#define COLOR_ORANGE "\033[31m" // cell value 3
#define COLOR_YELLOW "\033[31m" // cell value 2
#define COLOR_WHITE "\033[31m"  // cell value 1

#define WIDTH 40
#define HEIGHT 40

int init_grid(int height, int width, int (*positions)[width]);
int draw_new_positions();
int render();

int main() {
  int startup_status = 0;
  // gets terminal window size
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1) {
    fprintf(stderr, "Failed to get terminal window size");
    return 1;
  }

  int terminal_height = w.ws_row;
  int terminal_width = w.ws_col;

  // syntax is kind of confusing for these malloc blocks, I think it works?
  int (*positions)[terminal_width] =
      malloc(terminal_height * terminal_width * sizeof(int));
  if (positions == NULL) {
    fprintf(stderr, "Failed to allocate for positions");
    return 1;
  }
  memset(positions, 0, terminal_height * terminal_width * sizeof(int));

  int (*new_positions)[terminal_width] =
      malloc(terminal_height * terminal_width * sizeof(int));
  if (new_positions == NULL) {
    fprintf(stderr, "Failed to allocate for new_positions");
    free(positions);
    return 1;
  }
  memset(new_positions, 0, terminal_height * terminal_width * sizeof(int));

  printf("starting abellian sandpile simulation\n");
  printf("The terminal size is: %d rows, %d columns\n", terminal_height,
         terminal_width);
  startup_status = init_grid(terminal_height, terminal_width, positions);
  printf("\ninitialized grid");

  free(positions);
  free(new_positions);
  return 0;
}

int init_grid(int height, int width, int (*positions)[width]) {
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      // positions[i][j] = 0; // this shouldnt be needed but it is
      printf("%d", positions[i][j]);
    }
    printf("\n");
  }

  return 0;
}
