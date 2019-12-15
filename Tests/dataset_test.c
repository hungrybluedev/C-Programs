#include "dataset_test.h"
#include "../StdLib/Data/csv.h"
#include "../StdLib/Data/data.h"
#include "test.h"

#include <stdlib.h>
#include <string.h>

static char *test_new_record() {
  string_t *values[] = {
      convert_string("This"),
      convert_string("is"),
      convert_string("a"),
      convert_string("test"),
  };
  size_t num_bytes = sizeof(values);
  string_t **copy = malloc(num_bytes);
  memcpy(copy, values, num_bytes);

  record_t *record = new_record(num_bytes / sizeof(string_t *), copy);

  // Assert that the data is stored correctly.
  for (size_t i = 0; i < record->count; i++) {
    mu_assert("Strings are not equal.",
              string_cmp(values[i], record->values[i]) == 0);
  }

  free_record(record);
  return NULL;
}

static char *test_read_csv_record() {
  const char *filename = "data.csv";
  FILE *tmp = fopen(filename, "w");
  fprintf(tmp, "first,second,third");
  fclose(tmp);

  string_t *strA = convert_string("first");
  string_t *strB = convert_string("second");
  string_t *strC = convert_string("third");
  string_t **values = malloc(3 * sizeof(string_t *));
  values[0] = strA;
  values[1] = strB;
  values[2] = strC;

  record_t *recordA = new_record(3, values);

  tmp = fopen(filename, "r");
  record_t *recordB = read_csv_record(tmp);
  fclose(tmp);
  remove(filename);
  mu_assert("Records are different.", record_cmp(recordA, recordB) == 0);

  return NULL;
}

char *test_dataset() {
  mu_run_test(test_new_record);
  mu_run_test(test_read_csv_record);
  return NULL;
}