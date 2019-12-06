#include "string.h"
#include "../Panic/panic.h"
#include <stdlib.h>
#include <string.h>

static const char *EMPTY_STRING = "String pointer is empty.";

static void assert_not_null(const string_t *string) {
  if (!string) {
    panic(stderr, EMPTY_STRING);
  }
}

string_t *new_string(const size_t len) {
  string_t *string = malloc(sizeof(string_t));
  assert_not_null(string);
  string->data = malloc(len * sizeof(uint8_t));
  string->len = len;
  return string;
}

string_t *convert_string(const char *cstr) {
  string_t *string = new_string(strlen(cstr));
  assert_not_null(string);
  memcpy(string->data, cstr, string->len);
  return string;
}

string_t *copy_string(const string_t *string) {
  string_t *copy = malloc(sizeof(string_t));
  assert_not_null(copy);
  memcpy(copy->data, string->data, string->len);
  return copy;
}

void free_string(string_t *string) {
  if (!string) {
    return;
  }
  if (string->data) {
    free(string->data);
  }
  free(string);
}

void fprint_string(const string_t *string, FILE *output) {
  if (!string || string->len == 0) {
    return;
  }
  if (!output) {
    panic(stderr, "Output pointer is null.");
  }

  fwrite(string->data, sizeof(uint8_t), string->len, output);
}

string_t *concat_string(const string_t *left, const string_t *right) {
  assert_not_null(left);
  assert_not_null(right);

  string_t *string = new_string(left->len + right->len);
  memcpy(string->data, left->data, left->len);
  memcpy(string->data + left->len, right->data, right->len);

  return string;
}

void print_string(const string_t *string) { fprint_string(string, stdout); }

string_t *substring(const string_t *src, const size_t start, const size_t end) {
  assert_not_null(src);
  if (end > src->len) {
    panic(stderr, "Ending index exceeds the length of original string.");
  }
  if (start > src->len || end <= start) {
    panic(stderr, "Invalid constraints to extract substring from.");
  }
  if (start == 0 && end == src->len) {
    return copy_string(src);
  }

  size_t len = end - start;
  string_t *substr = new_string(len);
  memcpy(substr->data, src->data + start, len);

  return substr;
}

bool string_is_empty(const string_t *string) {
  assert_not_null(string);
  return string->len == 0;
}
string_t *left_string(const string_t *src, size_t len) {
  assert_not_null(src);
  if (len > src->len) {
    panic(stderr, "Desired length exceeds the length of the original string.");
  }
  if (len == src->len) {
    return copy_string(src);
  }
  string_t *leftstr = new_string(len);
  memcpy(leftstr->data, src->data, len);

  return leftstr;
}
string_t *right_string(const string_t *src, size_t len) {
  assert_not_null(src);
  if (len > src->len) {
    panic(stderr, "Desired length exceeds the length of the original string.");
  }
  if (len == src->len) {
    return copy_string(src);
  }
  string_t *rightstr = new_string(len);
  size_t offset = src->len - len;
  memcpy(rightstr->data, src->data + offset, len);

  return rightstr;
}

int string_cmp(const string_t *left, const string_t *right) {
  assert_not_null(left);
  assert_not_null(right);
  if (left->len != right->len) {
    return left->len > right->len ? +1 : -1;
  }
  for (size_t index = 0; index < left->len; index++) {
    int diff = left->data[index] - right->data[index];
    if (diff) {
      return diff;
    }
  }
  return 0;
}

size_t index_of_string(const string_t *bigger, const string_t *smaller) {
  assert_not_null(bigger);
  assert_not_null(smaller);
  const size_t fail_value = bigger->len + 1;
  if (smaller->len > bigger->len) {
    return fail_value;
  }
  if (smaller->len == bigger->len) {
    return string_cmp(smaller, bigger) ? fail_value : 0;
  }

  for (size_t i = 0; i <= bigger->len - smaller->len; i++) {
    bool mismatched = false;
    for (size_t j = 0; j < smaller->len; j++) {
      if (smaller->data[j] != bigger->data[i + j]) {
        mismatched = true;
        break;
      }
    }
    if (!mismatched) {
      return i;
    }
  }
  return fail_value;
}
