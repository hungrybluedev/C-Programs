///
/// © 2019 Subhomoy Haldar
///
/// This code is distributed under the MIT License.
/// Refer to the LICENSE.md file for more information.
///
/// Version - 2019-05-25
///

#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#define NULL_ARG "The argument is a null pointer."
#define INVALID_INDEX "The index provided is invalid."
#define EMPTY_SRC "The address of the element provided is invalid or empty."

/**
 * A convenient macro to obtain a pointer to the internal
 * data of the list which also supports pointer arithmetic.
 * It is recommended to use this internally and expose only
 * void * pointers to APIs.
 */
#define LIST_DATA(list) ((char *)(list)->data)

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * The struct to store the operational details for an ArrayList.
 *
 * A list is defined to be an indexable, iterable collection of
 * elements that supports arbitrary insertion, removal and
 * retrieval. These implementations deal with arrays containing
 * elements of the same datatype. Incompatible (irregular and of
 * different widths) types are not supported.
 *
 * An ArrayList is backed by an array (contiguous memory
 * space).
 *
 * An ArrayList has the following properties:
 *
 * +-----------+--------+-------------------------------------------+
 * | Property  | Type   | Description                               |
 * +-----------+--------+-------------------------------------------+
 * | length    | size_t | The current length or size of the list;   |
 * |           |        |   the number of elements.                 |
 * | capacity  | size_t | The number of elements that it can hold   |
 * |           |        |   without expanding.                      |
 * | width     | size_t | The width or size (in bytes) of the base  |
 * |           |        |   datatype.                               |
 * | data      | void*  | The storage for all elements of the list. |
 * +-----------+--------+-------------------------------------------+
 *
 * NOTE Always remember to initialize and free an ArrayList with the
 * appropriate methods provided.
 */
struct arr_list_struct {
  size_t length;
  size_t capacity;
  size_t width;
  void *data;
};

typedef struct arr_list_struct ArrayList;

// SECTION: Initialization and Deallocation methods.

/**
 * Initializes an empty ArrayList with the specified `capacity` and the
 * required `width` of the datatypes to be stored in the list.
 *
 * NOTE: It is recommended to supply the width of the base datatype using
 * the `sizeof()` keyword. This works for almost all possible cases.
 *
 * Whenever an ArrayList is initialized, do not forget to free it after
 * use. Initialization acquires resources, freeing deallocated them. It
 * is crucial in order to avoid memory leaks. Use `free_array_list(&list)`
 * to clear the allocated memory.
 *
 * +----------------+--------------+---------------------------------+
 * | Parameter name | Type         | Description                     |
 * +----------------+--------------+---------------------------------+
 * | list           | ArrayList*   | Pointer to an existing list.    |
 * | capacity       | size_t       | The desired initial capacity.   |
 * | width          | width        | The width of the base datatype. |
 * +----------------+--------------+---------------------------------+
 */
char *initialize_array_list(ArrayList *list, const size_t capacity,
                            const size_t width);

/**
 * Deallocates all the memory that had been acquired by an ArrayList.
 * This must be called after all work is completed with the aforementioned
 * ArrayList.
 *
 * +----------------+--------------+---------------------------------+
 * | Parameter name | Type         | Description                     |
 * +----------------+--------------+---------------------------------+
 * | list           | ArrayList*   | Pointer to an existing list.    |
 * +----------------+--------------+---------------------------------+
 */
char *free_array_list(ArrayList *list);

// SECTION Output function(s)

/**
 * Iterates through every element in the array and applies the function
 * provided to all elements (which generally means printing to the
 * specified stream).
 *
 * NOTE: Here's an example of how to use this function with integers:
 *
 * void display_int(FILE *out_stream, const size_t index, void *element)
 * {
 *     fprintf(out_stream, "%" PRIuMAX ". %d\n", index, *((int *)element));
 * }
 *
 * int main()
 * {
 *     // ...
 *     char *result = output_array_list(stdout, &list, display_int);
 *     // ...
 * }
 *
 * +----------------+--------------+----------------------------------+
 * | Parameter name | Type         | Description                      |
 * +----------------+--------------+----------------------------------+
 * | out_stream     | FILE*        | Pointer to the output stream.    |
 * | list           | ArrayList*   | Pointer to an existing list.     |
 * | (*display)     | function     | Function that operates on the    |
 * | -  out_stream  |  pointer     |  individual element of the list  |
 * | -  index       |              |  with the details and outputs to |
 * | -  element     |              |  out_stream.                     |
 * +----------------+--------------+----------------------------------+
 */
char *output_array_list(FILE *out_stream, const ArrayList *list,
                        const void (*display)(FILE *out_stream,
                                              const size_t index,
                                              const void *element));

// SECTION Functions for modification

/**
 * Adds the specified element to the last position in the ArrayList.
 * Increases the length of the ArrayList by 1. If necessary, it
 * automatically expands the storage to accomodate new elements.
 *
 * +----------------+--------------+-----------------------------------+
 * | Parameter name | Type         | Description                       |
 * +----------------+--------------+-----------------------------------+
 * | list           | ArrayList*   | Pointer to an existing list.      |
 * | element        | void*        | Pointer to the element to insert. |
 * +----------------+--------------+-----------------------------------+
 */
char *append_to_array_list(ArrayList *list, const void *element);

/**
 * Adds the elements of an array (the number of elements must
 * be specified by count) to the array list. The length of the
 * array list is increased by count.
 *
 * NOTE There is no bounds checking applied for the array. The
 * only information provided to the function is `count` and it
 * is assumed that it is within range of the array in question.
 * Caution must be exercised while supplying the count.
 *
 * Here is an example to show the intended usage:
 *
 * // ...
 * int elements[] = {1, 2, 3, 4, 5, 6};
 * const size_t width = sizeof(int);
 * const size_t size = sizeof(elements) / width;
 * // ...
 * ArrayList list = {};
 * char *result = initialize_array_list(&list, size, width);
 * // Check result...
 *
 * result = add_all_to_array_list(&list, elements, size);
 * // Check result...
 * // ...
 *
 * +----------------+--------------+-----------------------------------+
 * | Parameter name | Type         | Description                       |
 * +----------------+--------------+-----------------------------------+
 * | list           | ArrayList*   | Pointer to an existing list.      |
 * | array          | void*        | Pointer to the array.             |
 * | count          | size_t       | Number of elements to be copied.  |
 * +----------------+--------------+-----------------------------------+
 */
char *add_all_to_array_list(ArrayList *list, const void *array,
                            const size_t count);

/**
 * Inserts an element in the array list at the specified position.
 * Causes all the existing elements to shuffle up by one. It returns
 * an error message if the index specified is out of bounds. The
 * length of the array list is increased by 1.
 *
 * NOTE The index has to stay in the half-open range [0, list->length).
 * It *cannot* be equal to list->length. In that case, it is recommended
 * to use `append_to_array_list`.
 *
 * +----------------+--------------+-----------------------------------+
 * | Parameter name | Type         | Description                       |
 * +----------------+--------------+-----------------------------------+
 * | list           | ArrayList*   | Pointer to an existing list.      |
 * | index          | size_t       | The position to insert in.        |
 * | element        | void*        | Pointer to the element to insert. |
 * +----------------+--------------+-----------------------------------+
 */
char *insert_in_array_list(ArrayList *list, const size_t index,
                           const void *element);

/**
 * Deletes an item from the array list and causes the length to reduce
 * by 1. The element to be deleted is specified by the index, which
 * must be within bounds, failing which, an error message is returned.
 * It also causes the elements to shuffle down and preserve the
 * contiguous nature of the data.
 *
 * +----------------+--------------+-----------------------------------+
 * | Parameter name | Type         | Description                       |
 * +----------------+--------------+-----------------------------------+
 * | list           | ArrayList*   | Pointer to an existing list.      |
 * | index          | size_t       | The position to delete from.      |
 * +----------------+--------------+-----------------------------------+
 */
char *delete_index_array_list(ArrayList *list, const size_t index);

/**
 * Updates the list by replacing an existing element (specified by the
 * index provided) with a new element. This does not affect the length
 * of the array list.
 *
 * +----------------+--------------+-----------------------------------+
 * | Parameter name | Type         | Description                       |
 * +----------------+--------------+-----------------------------------+
 * | list           | ArrayList*   | Pointer to an existing list.      |
 * | index          | size_t       | The position to put value in.     |
 * | element        | void*        | Pointer to the element to insert. |
 * +----------------+--------------+-----------------------------------+
 */
char *set_in_array_list(ArrayList *list, const size_t index,
                        const void *element);

/**
 * Retrieves the value at the specified index and stores the result
 * in the destination provided. It does not affect the list.
 *
 * +----------------+--------------+-----------------------------------+
 * | Parameter name | Type         | Description                       |
 * +----------------+--------------+-----------------------------------+
 * | list           | ArrayList*   | Pointer to an existing list.      |
 * | index          | size_t       | The position to put value in.     |
 * | destination    | void*        | Pointer to the element's storage. |
 * +----------------+--------------+-----------------------------------+
 */
char *get_from_array_list(const ArrayList *list, const size_t index,
                          void *destination);

/**
 * Applies the specified function to all the elements in the array
 * list. The operation function has access to the index and a common
 * storage location (result), where it can update the final result
 * incrementally.
 *
 * +----------------+--------------+-----------------------------------+
 * | Parameter name | Type         | Description                       |
 * +----------------+--------------+-----------------------------------+
 * | list           | ArrayList*   | Pointer to an existing list.      |
 * | result         | void*        | Pointer to the common storage.    |
 * | (*func)        | function     | Function that calculates the      |
 * | -  *result     |  pointer     |  result on a per element basis.   |
 * | -  index       |              |                                   |
 * | -  *element    |              |                                   |
 * +----------------+--------------+-----------------------------------+
 */
char *apply_to_array_list(const ArrayList *list, void *result,
                          char *(*func)(void *result, const size_t index,
                                        const void *element));

/**
 * Linearly searches the Array for an element that satisfies
 * the condition function. It then stores the index of the
 * first occurence in the index_storage and returns (NULL).
 * If the search is unsuccessful, it returns a message:
 * "Search unsuccessful".
 *
 * +----------------+--------------+-------------------------------------------+
 * | Parameter name | Type         | Description                               |
 * +----------------+--------------+-------------------------------------------+
 * | list           | ArrayList*   | Pointer to an existing list.              |
 * | index_storage  | size_t       | Storage for index after succesful search. |
 * | (*condition)   | function     | Returns a boolean value based on the      |
 * | -  element     |  pointer     |  current element's eligibility.           |
 * +----------------+--------------+-------------------------------------------+
 */
char *search_array_list(const ArrayList *list, size_t *index_storage,
                        const bool (*condition)(void *element));
/**
 * Returns the result of comparison of two array lists.
 * An array list is said to be equal to another if
 * 1. It has the same length
 * 2. It has the same elements in the same order.
 *
 * If the lengths differ, the list with the smaller length is
 * said to be the "lesser" one. If the lengths are equal, the
 * point of difference is the first pair of elements which do
 * not match. Their (non-zero) comparison result is returned
 * as a result.
 *
 * +----------------+--------------+----------------------------------+
 * | Parameter name | Type         | Description                      |
 * +----------------+--------------+----------------------------------+
 * | listA          | ArrayList*   | Pointer to the first list.       |
 * | listB          | ArrayList*   | Pointer to the second list.      |
 * | (*cmp)         | function     | Returns an integer based on the  |
 * | -  element     |  pointer     |  current pair of elements.       |
 * +----------------+--------------+----------------------------------+
 */
int compare_array_lists(const ArrayList *listA, const ArrayList *listB,
                        const int (*cmp)(const void *elementA,
                                         const void *elementB));

#endif // ARRAY_LIST_H