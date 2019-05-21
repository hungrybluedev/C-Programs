///
/// © 2019 Subhomoy Haldar
///
/// This code is distributed under the MIT License.
/// Refer to the LICENSE.md file for more information.
///
/// Version - 2019-05-21
///

#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#define NULL_ARG "The argument is a null pointer."
#define INVALID_INDEX "The index provided is invalid."
#define EMPTY_SRC "The address of the element provided is invalid or empty."

#include <inttypes.h>

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
 */
struct arr_list_struct
{
    size_t length;
    size_t capacity;
    size_t width;
    void *data;
};

typedef struct arr_list_struct ArrayList;

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
char *initialize_array_list(ArrayList *list,
                            const size_t capacity,
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

/**
 * Iterates through every element in the array and applies the function
 * provided to all elements.
 * 
 * NOTE: Here's an example of how to use this function with integers:
 * 
 * void display_int(const size_t index, void *element)
 * {
 *     printf("%" PRIuMAX ". %d\n", index, *((int *)element));
 * }
 * 
 * int main()
 * {
 *     // ...
 *     char *result = display_array_list(&list, display_int);
 *     // ...
 * }
 * 
 * 
 */
char *display_array_list(const ArrayList *list,
                         const void (*display)(const size_t index, void *element));

char *append_to_array_list(ArrayList *list,
                           const void *element);

#endif //ARRAY_LIST_H