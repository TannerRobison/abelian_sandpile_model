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

int init_grid(int height, int width, int (*positions)[width]);
int get_new_positions(int height, int width, int (*positions)[width],
                      int (*new_positions)[width]);
int render(int height, int width, int (*positions)[width],
           int (*new_positions)[width]);

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

  int (*positions)[terminal_width] =
      malloc(terminal_height * terminal_width * sizeof(int));
  if (positions == NULL) {
    fprintf(stderr, "Failed to allocate for positions");
    return 1;
  }
  // fill array with zeros
  memset(positions, 0, terminal_height * terminal_width * sizeof(int));

  int (*new_positions)[terminal_width] =
      malloc(terminal_height * terminal_width * sizeof(int));
  if (new_positions == NULL) {
    fprintf(stderr, "Failed to allocate for new_positions");
    free(positions);
    return 1;
  }
  // fill array with zeros
  memset(new_positions, 0, terminal_height * terminal_width * sizeof(int));

  printf("The terminal size is: %d rows, %d columns\n", terminal_height,
         terminal_width);

  printf("starting abellian sandpile simulation\n");

  startup_status = init_grid(terminal_height, terminal_width, positions);
  if (startup_status) {
    fprintf(stderr, "Failed to initialize grid");
  }
  get_new_positions(terminal_width, terminal_width, positions, new_positions);

  free(positions);
  free(new_positions);
  return 0;
}

int init_grid(int height, int width, int (*positions)[width]) {
  printf("\033[H\033[J Starting abellian sandpile model.....\n");
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      printf(" ");
    }
    printf("\n");
  }
  return 0;
}

int get_new_positions(int height, int width, int (*positions)[width],
                      int (*new_positions)[width]) {
  new_positions = positions;

  // getting new positions
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; i++) {
      if (positions[i][j] >= 4) {
        // add some logic here
        new_positions[i][j] = 0;
        new_positions[i][j] = positions[i + 1][j] + 1;
        new_positions[i][j] = positions[i - 1][j] + 1;
        new_positions[i][j] = positions[i][j + 1] + 1;
        new_positions[i][j] = positions[i][j - 1] + 1;
      }
    }
  }
  return 0;
}

int render(int height, int width, int (*positions)[width],
           int (*new_positions)[width]) {
  return 0;
}
