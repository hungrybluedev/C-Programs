#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "minunit.h"
#include "list.h"

int tests_run = 0;

/**
 * Ensures that newly created ArrayLists behave.
 */
static char *empty_array_list_test()
{
    ArrayList list = {};
    // Test invalid conditions
    mu_assert(
        "Did not return error message stating positive capacity needed.",
        strcmp("Capacity must be positive.", initialize_array_list(&list, 0, 0)) == 0);

    mu_assert(
        "Did not return error message for invalid width.",
        strcmp("Invalid width. Use sizeof() operator to determine width of datatype.",
               initialize_array_list(&list, 1, 0)) == 0);

    // Check if list initializes properly
    mu_assert(
        "Could not initialize properly.",
        initialize_array_list(&list, 1, 1) == NULL);

    // Check the contents
    mu_assert("Incorrect length.", list.length == 0);
    mu_assert("Incorrect capacity.", list.capacity == 1);

    // Free the array list
    mu_assert("Could not free memory.", free_array_list(&list) == NULL);

    return NULL;
}

/**
 * Ensures that all the addition/append methods work, i.e.:
 * 1. append_to_array_list
 * 2. add_all_to_array_list
 */
static char *addition_to_list_works()
{
    ArrayList list = {};

    const size_t capacity = 5;
    const size_t width = sizeof(int);
    const int elements[] = {849, 25, 6, -8, 39};
    const size_t length = sizeof(elements) / width;

    // Initialize with set parameters
    mu_assert("Failed to initialize properly", initialize_array_list(&list, capacity, width) == NULL);

    for (size_t index = 0; index < length; index++)
    {
        mu_assert("Failed to insert element in array list.", append_to_array_list(&list, (void *)(elements + index)) == NULL);
    }

    // Check the values
    mu_assert("Invalid state: length does not match.", list.length == length);
    mu_assert("Invalid state: capacity does not match.", list.capacity == length);

    // Add more elements
    const int more[] = {95, -62, 7, -9, 38, -56};
    const size_t more_length = sizeof(more) / width;
    mu_assert("Could not add elements of array.", add_all_to_array_list(&list, more, more_length) == NULL);

    // Check again
    mu_assert("Invalid state after addition: length does not match.", list.length == (length + more_length));
    mu_assert("Invalid state after addition: capacity does not match.", list.capacity == 20);

    // Free the array list
    mu_assert("Could not free memory.", free_array_list(&list) == NULL);

    return NULL;
}

static char *remove_file(char *file)
{
    return remove(file)
               ? "There was an error while trying to delete the file."
               : NULL;
}

void print_double(FILE *out_stream, const size_t index, const void *element)
{
    fprintf(out_stream, "%" PRIuMAX ": %.2lf\n", index, *((double *)element));
}

/**
 * Ensures that the output function works correctly.
 */
static char *output_works_correctly()
{
    ArrayList list;
    const size_t width = sizeof(double);
    const double values[] = {0.1, 0.2, 0.3, 0.4, 0.45, 6.7, 78.9, 8.0, 91, 1.0};
    const double tolerance = 0.01;
    const size_t capacity = sizeof(values) / width;

    mu_assert("Could not initialize properly.", initialize_array_list(&list, capacity, width) == NULL);
    mu_assert("Could not add all the elements to the list.", add_all_to_array_list(&list, values, capacity) == NULL);

    char *filename = "output_works_correctly.tmp";
    FILE *temp_file = fopen(filename, "w");

    if (!temp_file)
    {
        return "Could not create and open temporary file for writing.";
    }

    mu_assert("Could not output to file.", output_array_list(temp_file, &list, print_double) == NULL);

    fclose(temp_file);
    // Data written to file successfully. Now read to ensure that the data matches.

    temp_file = fopen(filename, "r");

    if (!temp_file)
    {
        return "Could not create and open temporary file for reading.";
    }

    for (size_t index = 0; index < capacity; index++)
    {
        size_t index_data;
        double data;
        fscanf(temp_file, "%" SCNuMAX ": %lf", &index_data, &data);
        mu_assert("Content index does not match.", index_data == index);
        mu_assert("Content data does not match.", fabs(data - values[index]) <= tolerance);
    }

    fclose(temp_file);
    mu_assert("Could not remove the temporary file.", remove_file(filename) == NULL);

    mu_assert("Could not free the ArrayList.", free_array_list(&list) == NULL);
    return NULL;
}

static char *insertion_and_deletion_work()
{
    return "Not implemented yet.";
}

static char *set_and_get_work()
{
    return "Not implemented yet.";
}

static char *all_tests()
{
    mu_run_test(empty_array_list_test);
    mu_run_test(addition_to_list_works);
    mu_run_test(output_works_correctly);
    mu_run_test(insertion_and_deletion_work);
    return NULL;
}

int main(int argc, char const *argv[])
{
    char *result = all_tests();
    if (result != 0)
    {
        printf("%s\n", result);
    }
    else
    {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);

    return result != 0;
}
