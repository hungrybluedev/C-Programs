#include "string_test.h"
#include "../StdLib/String/string.h"
#include "test.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

static FILE *tmp;
static char *m;

/**
 * Internal utility to remove temporary files from disk. Temporary
 * files are created during testing.
 */
static char *remove_file(const char *temp_file) {
  return remove(temp_file)
             ? "There was an error while trying to delete the temp_file."
             : NULL;
}

static char *eq_len_str_cmp() {
  const char *ref = "This is a sample!";
  string_t *a = convert_string(ref);
  string_t *b = new_string(strlen(ref));

  mu_assert("Different strings seem equal.", string_cmp(a, b) != 0);

  for (size_t idx = 0; idx < b->len; idx++) {
    b->data[idx] = (uint8_t)ref[idx];
  }

  mu_assert("Equal strings seem different.", string_cmp(a, b) == 0);

  free_string(a);
  free_string(b);
  return NULL;
}

static char *diff_len_str_cmp() {
  string_t *a = convert_string("AAAA");
  string_t *b = convert_string("AABA");

  mu_assert("String comparison sign is wrong.", string_cmp(a, b) < 0);
  mu_assert("String comparison sign is wrong.", string_cmp(b, a) > 0);
  mu_assert("Equal string gives non-zero comparison result.",
            string_cmp(a, a) == 0);
  mu_assert("Equal string gives non-zero comparison result.",
            string_cmp(b, b) == 0);

  free_string(a);
  return NULL;
}

static char *fprint_works() {
  const char *filename = "string_printf_test.tmp";

  tmp = fopen(filename, "w");

  string_t *strA = convert_string("This is the first line to be printed.\n");
  string_t *strB =
      convert_string("This is the second line.\nThere's another!\n");

  fprint_string(strA, tmp);
  fprint_string(strB, tmp);

  fclose(tmp);
  tmp = fopen(filename, "r");

  char buf[64];
  char *buffer = buf;
  size_t bufsize = 0;
  size_t len = 0;

  len = getline(&buffer, &bufsize, tmp);
  string_t *line1 = convert_string(buffer);
  mu_assert("Different length of line.", len == strA->len);

  len = getline(&buffer, &bufsize, tmp);
  string_t *line2 = convert_string(buffer);

  len += getline(&buffer, &bufsize, tmp);
  string_t *line3 = convert_string(buffer);

  string_t *line2and3 = concat_string(line2, line3);
  mu_assert("Different length of lines 2 and 3.", len == strB->len);

  free(buffer);

  mu_assert("First line was different.", string_cmp(strA, line1) == 0);
  mu_assert("Second line was different.", string_cmp(strB, line2and3) == 0);

  fclose(tmp);
  free_string(strA);
  free_string(strB);
  free_string(line1);
  free_string(line2);
  free_string(line2and3);

  if ((m = remove_file(filename))) {
    return m;
  }
  return NULL;
}

char *test_string() {
  mu_run_test(eq_len_str_cmp);
  mu_run_test(diff_len_str_cmp);
  mu_run_test(fprint_works);
  return NULL;
}