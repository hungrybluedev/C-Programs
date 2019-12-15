#ifndef C_PROGRAMS_STRING_H
#define C_PROGRAMS_STRING_H
/**
 * A better, safer string type for C.
 *
 * Note that almost all the methods return newly allocated strings. It is up to
 * the user to remember to free them using the free_string function.
 */
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * A struct for a safer, length-prefixed string type for C.
 *
 * The actual size (in bytes) varies, depending on the size of the size_t
 * datatype. It is recommended to use new_string and convert_string functions
 * to initialize required string_t's properly and with relative ease.
 *
 * It is also important to free the allocated strings using the free_string
 * function.
 */
typedef struct string {
  size_t len;
  uint8_t *data;
} string_t;

/**
 * Allocates space for a new string_t with the desired length.
 *
 * @param len The desired length of the new string.
 * @return A (hopefully non-null) string_t initialized properly.
 */
string_t *new_string(size_t len);

/**
 * Converts a vanilla char* C string to a string_t version. It is
 * imperative to ensure that the string passed in is non-null, otherwise
 * the program will exit with a failure (EXIT_FAILURE).
 *
 * @param cstr The "normal" C string to be converted.
 * @return A string_t pointer with the same data as the given C string.
 */
string_t *convert_string(const char *cstr);
/**
 * Copies an existing (non-null) string_t to another (newly allocated)
 * string_t with the same data.
 *
 * @param string The string_t to be copied.
 * @return A deep copy of the given string_t.
 */
string_t *copy_string(const string_t *string);

string_t *first_n(const char *cstr, size_t n);

/**
 * De-allocates the memory consumed by the given (non-null) string_t.
 * It de-allocates both the internal data pointer and the string_t pointer.
 *
 * @param string The string_t to be deallocated.
 */
void free_string(string_t *string);

/**
 * A utility method to output the contents of the given string_t to
 * the standard output. It makes use of the fprint_string function.
 *
 * @param string The string_t to be printed.
 */
void print_string(const string_t *string);

/**
 * A utility method to output the contents of the given string_t to
 * the output stream specified. Both parameters must be non-null.
 *
 * @param string The string_t to be printed.
 * @param output The file pointer to output the string to.
 */
void fprint_string(const string_t *string, FILE *output);

/**
 * Concatenates the two strings (both must be non-null) together and
 * returns the concatenation as a newly allocated string_t.
 *
 * @param left  The first string_t.
 * @param right The second string_t.
 * @return The concatenation of left and right as a new string_t.
 */
string_t *concat_string(const string_t *left, const string_t *right);

/**
 * Creates a newly-allocated substring that contains the contents of the
 * source string (src) from the starting index (inclusive) to the ending
 * index (exclusive).
 *
 * @param src   The string_t to create the substring from.
 * @param start The starting index (inclusive).
 * @param end   The ending index (exclusive).
 * @return A substring that has been newly allocated.
 */
string_t *substring(const string_t *src, size_t start, size_t end);

/**
 * @param string The string to check.
 * @return true if it is empty, i.e. length is 0.
 */
bool string_is_empty(const string_t *string);

/**
 * Extracts the desired number of characters from the left part (beginning) of
 * the given string_t as a new string_t.
 *
 * @param src The string to extract from.
 * @param len The number of characters desired.
 * @return A substring containing "len" characters of src from the left.
 */
string_t *left_string(const string_t *src, size_t len);

/**
 * Extracts the desired number of characters from the right part (ending) of
 * the given string_t as a new string_t.
 *
 * @param src The string to extract from.
 * @param len The number of characters desired.
 * @return A substring containing "len" characters of src from the right.
 */
string_t *right_string(const string_t *src, size_t len);

/**
 * Performs a comparison of the given two strings and returns:
 * - a negative number if the left string is lexicographically less (or comes
 *   earlier in dictionary order) than the right string.
 * - a positive number if the left string appears after the right one.
 * - zero if they are equal.
 *
 * @param left  The left string to compare.
 * @param right The right string to compare.
 * @return An integer based on the comparison of the two strings given.
 */
int string_cmp(const string_t *left, const string_t *right);

/**
 * Checks if the smaller string is entirely contained in the bigger one.
 * If it is, it returns the first index where the two string start to match.
 * If it is not present, it returns an index outside the string (greater
 * than the length of the string).
 *
 * @param bigger  The string to be searched in.
 * @param smaller The string to be searched for.
 * @return The location of the first match.
 */
size_t index_of_string(const string_t *bigger, const string_t *smaller);

#endif // C_PROGRAMS_STRING_H