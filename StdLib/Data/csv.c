#include "csv.h"
#include "../String/string.h"
#include "data.h"

#include <string.h>

static size_t count_columns(char *line) {
  size_t count = 1;
  while (*line) {
    if (*line == ',')
      count++;
    line++;
  }
  return count;
}

static record_t *extract_data(char *line) {
  size_t count = count_columns(line);
  char *prev = NULL;
  char *curr = line;
  size_t running_count = 0;
  size_t index = 0;

  string_t **data = malloc(sizeof(string_t *) * count);

  while (*curr) {
    if (!prev) {
      prev = curr;
      running_count = 0;
    }
    if (*curr == ',') {
      data[index++] = first_n(prev, running_count);
      prev = NULL;
    }
    curr++;
    running_count++;
  }
  // Here's where we deal with the last column
  if (prev) {
    data[index++] = first_n(prev, running_count);
  }
  // We can free the buffer here because a copy of the data is stored in
  // the generated strings.
  free(line);
  return new_record(count, data);
}

record_t *read_csv_record(FILE *input) {
  char *line = NULL;
  size_t buffer_size = 0;
  ssize_t length = getline(&line, &buffer_size, input);

  // If we reach the end of the file, we return NULL
  // If the string is empty we also return NULL
  if (length == EOF || length == 0) {
    return NULL;
  }

  return extract_data(line);
}