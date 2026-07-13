#include <asm-generic/ioctls.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define CLEAR_GRID "\033[1;1H\033[2J"
#define COLOR_RED "\033[31m"    // cell value 4
#define COLOR_ORANGE "\033[31m" // cell value 3
#define COLOR_YELLOW "\033[33m" // cell value 2
#define COLOR_WHITE "\033[37m"  // cell value 1

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

  uint32_t time_steps = 4000000000; //4 billion time steps
  for (int i = 0; i < time_steps; i++) {
    // drop a 'grain' of sand of top of sandpile
    for (int j = 0; j < 100000; j++) {
      positions[terminal_height / 2][terminal_width / 2] += 1;
      get_new_positions(terminal_height, terminal_width, positions,
                        new_positions);
    }
    printf("time step: %u", (unsigned int)time_steps);
    printf(CLEAR_GRID);
    render(terminal_height, terminal_width, positions, new_positions);
  }

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
  memset(new_positions, 0, width * height * sizeof(int));
  // getting new positions
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      if (positions[i][j] >= 4) {
        new_positions[i][j] = 0; // Current cell becomes stable

        // Distribute sand to neighboring cells
        if (i + 1 < height)
          new_positions[i + 1][j] += 1; // Down
        if (i - 1 >= 0)
          new_positions[i - 1][j] += 1; // Up
        if (j + 1 < width)
          new_positions[i][j + 1] += 1; // Right
        if (j - 1 >= 0)
          new_positions[i][j - 1] += 1; // Left
      } else {
        new_positions[i][j] += positions[i][j]; // Stable cells remain the same
      }
    }
  }
  memcpy(positions, new_positions, height * width * sizeof(int));
  return 0;
}

int render(int height, int width, int (*positions)[width],
           int (*new_positions)[width]) {
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      if (new_positions[i][j] == 0) {
        printf(" "); // Empty cell
      } else if (new_positions[i][j] == 1) {
        printf(COLOR_WHITE "o"); // Cell with value 1
      } else if (new_positions[i][j] == 2) {
        printf(COLOR_YELLOW "0"); // Cell with value 2
      } else if (new_positions[i][j] == 3) {
        printf(COLOR_ORANGE "@"); // Cell with value 3
      } else if (new_positions[i][j] >= 4) {
        printf(COLOR_RED "#"); // Cell with value 4 or more
      }
    }
    printf("\n"); // Move to the next line after each row
  }
  return 0;
}
