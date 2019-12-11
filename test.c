#include "Tests/test.h"
#include "Tests/string_test.h"
#include "Tests/arraylist_test.h"
#include <stdio.h>
#include <stdlib.h>

size_t test_count = 0;
size_t tests_passed = 0;
size_t tests_run = 0;

typedef char *(*test_func)();

test_func tests[] = {
    test_arraylist,
    test_string
};

static char *all_test_modules() {
  char *message = NULL;
  for (size_t idx = 0; idx < sizeof(tests) / sizeof(test_func); idx++) {
    if (message) {
      break;
    }
    message = tests[idx]();
  }
  return message;
}

int main() {
  char *message = all_test_modules();
  if (message) {
    printf("Error occurred:\n%s\n", message);
  }

  printf("Total number of tests run    : %zu\n", tests_run);
  printf("Total number of tests passed : (%zu/%zu)\n", tests_passed, test_count);
  return EXIT_SUCCESS;
}