#include "data.h"

void free_record(record_t *record) {
  if (!record) {
    return;
  }
  for (size_t i = 0; i < record->count; i++) {
    free_string(record->values[i]);
  }
  free(record->values);
  free(record);
}

void free_cache(string_cache_t *cache) {
  if (!cache) {
    return;
  }
  for (size_t i = 0; i < cache->rows; i++) {
    free_record(cache->records[i]);
  }
  free(cache->records);
  free(cache);
}

void free_dataset(dataset_t *dataset) {
  if (!dataset) {
    return;
  }
  free(dataset->col_arr);
  free(dataset->row_arr);
  free_cache(dataset->cache);
  free(dataset);
}
record_t *new_record(size_t count, string_t **values) {
  record_t *result = malloc(sizeof(record_t));
  result->count = count;
  result->values = values;
  return result;
}

int record_cmp(const record_t *left, const record_t *right) {
  // Handling null cases. Null is considered to be lesser value than
  // that of all non-null values. This also facilitates moving the null
  // entries up to be spotted earlier.
  if (!left && !right) {
    return 0;
  }
  if (!left) {
    return -1;
  }
  if (!right) {
    return +1;
  }
  if (left->count != right->count) {
    return left->count > right->count ? +1 : -1;
  }
  for (size_t i = 0; i < left->count; i++) {
    int result = string_cmp(left->values[i], right->values[i]);
    if (result) {
      return result;
    }
  }
  return 0;
}
