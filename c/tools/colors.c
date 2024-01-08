#include <stdio.h>

int main() {
  int i = 0;
  while (i < 16) {
    int j = 0;
    while (j < 16) {
      int code = j + 16 * i;
      printf("\033[38;5;%dm%4d\033[0m", code, code);
      j++;
    }
    printf("\n");
    i++;
  }

  return 0;
}
