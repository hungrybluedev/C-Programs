///
/// © 2019 Subhomoy Haldar
///
/// This code is distributed under the MIT License.
/// Refer to the LICENSE.md file for more information.
///
/// Version - 2019-05-21
///

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <inttypes.h>

// Obtain a char * pointer to the list's void * data
#define LIST_DATA(list) ((char *)(list)->data)

#include "list.h"

// NOTE: The Comment Anchor plugin in vscode is quite helpful.
// NOTE: Why is there a relatively large amount of redundancy in my code?
//       Especially for validation tests?
// Ans: It's because I felt abstracting them to separate functions would
// only increase the complexity of my code and as is, they are simple
// enough to not be much of a concern. If you disagree and think that there's
// a better way, then by all means, let me know about it. My Twitter handle
// is @HungryBlueDev. DM or Tweet at me.

// SECTION Allocation and deallocation of memory.

char *initialize_array_list(ArrayList *list,
                            const size_t capacity,
                            const size_t width)
{
    // Perform basic validation tasks.
    if (!list)
    {
        return NULL_ARG;
    }
    if (capacity == 0)
    {
        return "Capacity must be positive.";
    }
    if (width == 0)
    {
        return "Invalid width. Use sizeof() operator to determine width of datatype.";
    }

    // Initialization can proceed.
    list->length = 0;
    list->capacity = capacity;
    list->width = width;
    list->data = malloc(capacity * width);

    // Check if the data was initialized properly.
    if (!(list->data))
    {
        return "Error occurred while allocating memory.";
    }
    return NULL;
}

char *free_array_list(ArrayList *list)
{
    if (!list)
    {
        return NULL_ARG;
    }
    free(list->data);
    return NULL;
}

// SECTION Display methods; useful for debugging.

char *output_array_list(FILE *out_stream,
                        const ArrayList *list,
                        const void (*display)(
                            FILE *out_stream,
                            const size_t index,
                            const void *element))
{
    if (!list)
    {
        return NULL_ARG;
    }
    for (size_t index = 0; index < list->length; index++)
    {
        (*display)(out_stream, index, LIST_DATA(list) + (index * list->width));
    }
    return NULL;
}

// SECTION Micro manipulation methods. For adding, removing, changing single items.

static char *_update_storage_size_(ArrayList *list,
                                   const size_t new_capacity)
{
    list->data = realloc(list->data, new_capacity * list->width);
    if (!list->data)
    {
        return "Ran out of memory and could not extend the capacity.";
    }
    list->capacity = new_capacity;
    return NULL;
}

static char *_extend_storage_(ArrayList *list)
{
    // Extend the storage to double the current amount
    return _update_storage_size_(list, list->capacity * 2);
}

static char *_shrink_storage_(ArrayList *list)
{
    // Shrink the storage to half the current amount
    return _update_storage_size_(list, list->capacity / 2);
}

char *append_to_array_list(ArrayList *list,
                           const void *element)
{
    if (!list)
    {
        return NULL_ARG;
    }
    if (!element)
    {
        return EMPTY_SRC;
    }
    // Check if we have enough space
    if (list->length == list->capacity)
    {
        char *result = _extend_storage_(list);
        if (result)
        {
            return result;
        }
    }
    // Copy the element to the required location
    memcpy(LIST_DATA(list) + (list->length * list->width), element, list->width);
    // Increment the value of length
    list->length++;
    return NULL;
}

char *add_all_to_array_list(ArrayList *list,
                            const void *array,
                            const size_t count)
{
    if (!list)
    {
        return NULL_ARG;
    }
    if (!array)
    {
        return EMPTY_SRC;
    }
    size_t new_length = list->length + count;

    // Check if we have enough space. Sometimes,
    // one expansion might not be enough. Repeat until
    // we are fully capable of accomodating all.
    while (new_length > list->capacity)
    {
        char *result = _extend_storage_(list);
        if (result)
        {
            return result;
        }
    }
    // Copy the elements to the required location
    memcpy(LIST_DATA(list) + (list->length * list->width), array, list->width * count);

    // Update the value of length
    list->length = new_length;

    return NULL;
}

char *set_in_array_list(ArrayList *list,
                        const size_t index,
                        const void *element)
{
    if (!list)
    {
        return NULL_ARG;
    }
    if (index >= list->length)
    {
        return INVALID_INDEX;
    }
    if (!element)
    {
        return EMPTY_SRC;
    }
    memcpy(LIST_DATA(list) + list->width * index, element, list->width);
    return NULL;
}

char *get_from_array_list(const ArrayList *list,
                          const size_t index,
                          void *destination)
{
    if (!list)
    {
        return NULL_ARG;
    }
    if (index > list->length)
    {
        return INVALID_INDEX;
    }
    if (!destination)
    {
        return "Null destination. Please provide a valid destination address.";
    }
    memcpy(destination, (LIST_DATA(list) + list->width * index), list->width);

    return NULL;
}

char *insert_in_array_list(ArrayList *list,
                           const size_t index,
                           const void *element)
{
    if (!list)
    {
        return NULL_ARG;
    }
    if (index > list->length)
    {
        return INVALID_INDEX;
    }
    if (!element)
    {
        return EMPTY_SRC;
    }
    size_t move_length = list->length - index;
    char *location = (LIST_DATA(list) + list->width * index);

    // Check if we have enough space
    if (list->length == list->capacity)
    {
        char *result = _extend_storage_(list);
        if (result)
        {
            return result;
        }
    }

    // Keep the destination 1 (width) higher, to accomodate for the new element.
    // memmove works in bytes, so everything needs to be multiplied by the width.
    memmove(location + list->width, location, move_length * list->width);

    // Copy the new element in position.
    memcpy(LIST_DATA(list) + list->width * index, element, list->width);

    // Increment the value of length
    list->length++;

    return NULL;
}

char *delete_index_array_list(ArrayList *list,
                              const size_t index)
{
    // Standard validation tests
    if (!list)
    {
        return NULL_ARG;
    }
    if (index > list->length)
    {
        return INVALID_INDEX;
    }

    // Overwrite the data with the elements that follow it.
    if (index < list->length - 1)
    {
        char *location = (LIST_DATA(list) + list->width * index);
        size_t move_length = list->length - index;
        memmove(location, location + list->width, move_length * list->width);
    }

    // Decrease the length by 1
    list->length--;

    // If it is just the last element, we clear it away anyway afterwards
    memset((char *)list->data + list->length * list->width, 0, list->width);

    char *result = NULL;
    // If the current length is less than a quarter of the current capacoty
    // we might be wasting space. So we halve the space consumption.
    if (list->length < list->capacity / 4)
    {
        result = _shrink_storage_(list);
    }

    return result;
}

// SECTION Searching, Comparison and function application

// NOTE I make liberal use of casts to char * type from
// the void * type. This is because while void * is good
// for holding any type of data, it does not allow any
// pointer arithmetic on it. char * does allow arithmetic,
// but using it throughout would mean more work for the
// end user. Therefore, I use char * internally, while
// exposing only void * endpoints to the public.

char *apply(const ArrayList *list,
            void *result,
            char *(*func)(
                void *result,
                const size_t index,
                const void *element))
{
    char *pointer = (char *)list->data;
    for (size_t index = 0; index < list->length; index++)
    {
        char *message;
        if ((message = func(result, index, (void *)pointer)))
        {
            return message;
        }
    }
    return NULL;
}

char *search(const ArrayList *list,
             size_t *index_storage,
             const bool (*condition)(void *elementA))
{
    char *pointer = (char *)list->data;
    for (size_t index = 0; index < list->length; index++, pointer += list->width)
    {
        if (condition((void *)pointer))
        {
            *index_storage = index;
            return NULL;
        }
    }
    return "Search unsuccessful";
}

int compare_array_lists(const ArrayList *listA,
                        const ArrayList *listB,
                        const int (*cmp)(const void *elementA, const void *elementB))
{
    if (!listA)
    {
        // Ordering is set as null < non-null;
        return listB == 0 ? 0 : -1;
    }
    if (!listB)
    {
        return 1;
    }
    // Compare with respect to number of elements first.
    if (listA->length != listB->length)
    {
        return (int)(listA->length - listB->length);
    }
    // Lengths are equal, compare each element
    char *pointerA = LIST_DATA(listA);
    char *pointerB = LIST_DATA(listB);
    size_t step = listA->width;
    for (size_t index = 0; index < listA->length; index++, pointerA += step, pointerB += step)
    {
        int cmp_result = cmp((void *)pointerA, (void *)pointerB);
        if (cmp_result)
        {
            return cmp_result;
        }
    }
    return 0;
}