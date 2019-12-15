#ifndef C_PROGRAMS_DATA_H
#define C_PROGRAMS_DATA_H

#include "../String/string.h"
#include <stdlib.h>

typedef struct record {
  size_t count;
  string_t **values;
} record_t;

typedef struct string_cache {
  size_t cols;
  size_t rows;
  record_t *header;
  record_t **records;
} string_cache_t;

typedef struct dataset {
  size_t cols;
  size_t rows;
  size_t *row_arr;
  size_t *col_arr;
  string_cache_t *cache;
} dataset_t;

/**
 * Note: The record created will contain a reference to the string
 * array provided. So any changes made on the original string array
 * will be reflected in the record. If a deep copy is preferred, it is
 * recommended to create a new array and deep copy the contents.
 *
 * @param count  The number of columns.
 * @param values The strings to be stored inside the record.
 * @return A new record containing the corresponding values.
 */
record_t *new_record(size_t count, string_t *values[]);

/**
 * Note: Do not call any of the free functions if the actual source
 * of data is a concrete, statically defined array of string_t*'s. Deallocate
 * only when the source of data is allocated manually (and not de-allocated
 * later on). The latter is the intended use case, which should happen most of
 * the time in the real world, so the use of free_(..) functions are recommended
 * when data is read in, processed and stored dynamically. The cleanup is
 * handled by this one call, so need to cleanup the original data later.
 */

void free_record(record_t *record);
void free_cache(string_cache_t *cache);
void free_dataset(dataset_t *dataset);

int record_cmp(const record_t *left, const record_t *right);

#endif // C_PROGRAMS_DATA_H
