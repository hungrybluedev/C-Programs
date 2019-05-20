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
#include <inttypes.h>

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
    if (capacity <= 0)
    {
        return "Capacity must be positive.";
    }
    if (width <= 0)
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

char *display_array_list(const ArrayList *list,
                         const void (*display)(const size_t index, void *element))
{
    if (!list)
    {
        return NULL_ARG;
    }
    for (size_t index = 0; index < list->length; index++)
    {
        (*display)(index, ((char *)list->data) + (index * list->width));
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
    memcpy(((char *)list->data) + (list->length * list->width), element, list->width);
    // Increment the value of length
    list->length++;
    return NULL;
}

char *set_array_list(ArrayList *list,
                     const size_t index,
                     const void *element)
{
    if (!list)
    {
        return NULL_ARG;
    }
    if (index < 0 || index >= list->length)
    {
        return INVALID_INDEX;
    }
    if (!element)
    {
        return EMPTY_SRC;
    }
    memcpy(((char *)list->data) + list->width * index, element, list->width);
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
    if (index < 0 || index > list->length)
    {
        return INVALID_INDEX;
    }
    if (!element)
    {
        return EMPTY_SRC;
    }
    size_t move_length = list->length - index;
    char *location = ((char *)list->data) + list->width * index;
    
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
    memcpy(((char *)list->data) + list->width * index, element, list->width);
    return NULL;
}

//// Temporary functions for testing code. Will not be shipped.
//// TODO: Remove once done.

void checkResult(char *message)
{
    if (message)
    {
        printf("%s\n", message);
        exit(EXIT_FAILURE);
    }
}

void display_int(const size_t index, void *element)
{
    printf("%" PRIuMAX ". %d\n", index, *((int *)element));
}

int main(int argc, char const *argv[])
{
    const size_t capacity = 3;
    const size_t width = sizeof(int);
    const int vals[] = {10, 20, 30, 40, 50, 60};

    const int new_val1 = 25;
    const int new_val2 = 20;

    ArrayList list = {};
    checkResult(initialize_array_list(&list, capacity, width));

    for (size_t index = 0; index < sizeof(vals) / width; index++)
    {
        checkResult(append_to_array_list(&list, (void *)(vals + index)));
    }

    checkResult(set_array_list(&list, 2, &new_val1));
    checkResult(insert_in_array_list(&list, 2, &new_val2));
    checkResult(display_array_list(&list, display_int));
    
    
    checkResult(free_array_list(&list));

    printf("Size of ArrayList is %" PRIuMAX "\n", list.length);
    printf("Capacity of ArrayList is %" PRIuMAX "\n", list.capacity);

    return EXIT_SUCCESS;
}
