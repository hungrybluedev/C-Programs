#include <stdio.h>
#include <stdlib.h>

void panic(FILE *output, const char *message) {
  fprintf(output, "Program panicked with the following message:\n\n%s\n\n",
          message);
  exit(EXIT_FAILURE);
}
