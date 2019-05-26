#include <stdlib.h>
#include <stdio.h>
#include "../list.h"

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

    if (result)
    {
        perror("Could not initialize array list.");
        return EXIT_FAILURE;
    }

    char ch;
    double current;
    do
    {
        // Enter numbers like:
        // 10[Enter]20[Enter]30[Ctrl+Z] - for Windows
        // 10[Enter]20[Enter]30[Ctrl+D] - for Unix/Linux, etc
        scanf("%lf%c", &current, &ch);
        result = append_to_array_list(&list, &current);

        if (result)
        {
            perror("Could not append to the array list.");
            return EXIT_FAILURE;
        }
    } while (ch == '\n');

    double sum = 0, average;
    result = apply_to_array_list(&list, &sum, operate_sum);

    average = sum / list.length;

    if (result)
    {
        perror("Failed to calculate the sum of elements.");
        return EXIT_FAILURE;
    }

    double max;
    result = apply_to_array_list(&list, &max, find_max);

    if (result)
    {
        perror("Failed to calculate the max element.");
        return EXIT_FAILURE;
    }

    printf("The sum of the elements is %.2lf\n", sum);
    printf("The average of the elements is %.2lf\n", average);
    printf("The maximum element is %.2lf\n", max);

    result = free_array_list(&list);

    if (result)
    {
        perror("Could not deallocate memory for array list.");
        return EXIT_FAILURE;
    }

    return result != NULL;
}