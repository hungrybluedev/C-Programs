# Array List

## Definition

### List

A list is an indexable, iterable collection of elements that
supports arbitrary insertion, deletion and retrieval. The order
of elements is well-defined, and can be used to distinguish
one list from another in case they have the same set of elements.

### ArrayList

An ArrayList (or Array List) is an array-based implementation of
the List ADT (Abstract Data Type). It uses an internal array
(contiguous memory location) to store the data. Being an array,
it does not allow data-types of varying types (widths).

## Motivation

The default arrays in C are static and although they can be resized
at run-time, they are very tedious to use. This module offers a
simple, plug-and-play solution for simple programs that just need
dynamic arrays with the ability to operate on data easily. The
expansion and compression of the existing data array is done
automatically and the user can focus solely on adding, removing
and retrieving data from the array list.

## Examples

The error checking has not been included to make the code more
readable for reference. It is recommend to always check for
errors. Helps in debugging. For the full source, check the `examples` folder.

### Reading the entire contents of a file to a string

```c
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

int main()
{
    ArrayList chars = {};
    const size_t initial_capacity = 128;
    char *result = initialize_array_list(&chars, initial_capacity, sizeof(char));

    int ch;
    const char END_OF_STRING = '\0';

    // Use Ctrl + Z on Windows and Ctrl + D on Unix based
    // systems to trigger enter the end of file character (EOF)
    while ((ch = getchar()) != EOF)
    {
        result = append_to_array_list(&chars, &ch);
    }
    result = append_to_array_list(&chars, &END_OF_STRING);

    printf("The string read was:\n\n%s\n", LIST_DATA(&chars));

    result = free_array_list(&chars);

    return result != NULL;
}
```

### Calculating the average and the extremes of all numbers in a file

```c
#include <stdlib.h>
#include <stdio.h>
#include "/list.h"

static char *operate_sum(void *storage, const size_t index, const void *element)
{
    double *sum = (double *)storage;
    *sum += *((double *)element);
    return NULL;
}

static char *find_max(void *storage, const size_t index, const void *element)
{
    double *max = (double *)storage;
    double dval = *(double *)element;
    if (index == 0 || *max < dval)
    {
        *max = dval;
    }
    return NULL;
}

int main()
{
    ArrayList list = {};
    const size_t width = sizeof(double);
    char *result = initialize_array_list(&list, 16, width);

    char ch;
    double current;
    do
    {
        // Enter numbers like:
        // 10[Enter]20[Enter]30[Ctrl+Z] - for Windows
        // 10[Enter]20[Enter]30[Ctrl+D] - for Unix/Linux, etc
        scanf("%lf%c", &current, &ch);
        result = append_to_array_list(&list, &current);
    } while (ch == '\n');

    double sum = 0, average;
    result = apply_to_array_list(&list, &sum, operate_sum);
    average = sum / list.length;

    double max;
    result = apply_to_array_list(&list, &max, find_max);

    printf("The sum of the elements is %.2lf\n", sum);
    printf("The average of the elements is %.2lf\n", average);
    printf("The maximum element is %.2lf\n", max);

    result = free_array_list(&list);
    return result != NULL;
}
```

## Performance

If the cost of copying elements using memcpy, memmove, etc is considered
to be constant (because `width` is constant throughout), then insertion,
deletion, searching, display, and all functions which invlove traversing
or processing all the elements of the array list are of linear time
complexity. Appending elements takes constant time, along with initialization,
and deallocation.

## Reference
