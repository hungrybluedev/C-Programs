#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include "minunit.h"
#include "list.h"

int tests_run = 0;

char *filename;
FILE *temp_file;

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

static char *remove_file(char *temp_file)
{
    return remove(temp_file)
               ? "There was an error while trying to delete the temp_file."
               : NULL;
}

static void print_double(FILE *out_stream, const size_t index, const void *element)
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

    filename = "output_works_correctly.tmp";
    temp_file = fopen(filename, "w");

    if (!temp_file)
    {
        return "Could not create and open temporary temp_file for writing.";
    }

    mu_assert("Could not output to temp_file.", output_array_list(temp_file, &list, print_double) == NULL);

    fclose(temp_file);
    // Data written to temp_file successfully. Now read to ensure that the data matches.

    temp_file = fopen(filename, "r");

    if (!temp_file)
    {
        return "Could not create and open temporary temp_file for reading.";
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
    mu_assert("Could not remove the temporary temp_file.", remove_file(filename) == NULL);

    mu_assert("Could not free the ArrayList.", free_array_list(&list) == NULL);
    return NULL;
}

static void print_uint64_t(FILE *out_stream, const size_t index, const void *element)
{
    fprintf(out_stream, "%" PRIuMAX ": %" PRIu64 "\n", index, *((uint64_t *)element));
}

static char *insertion_and_deletion_work()
{
    ArrayList list = {};
    const size_t capacity = 5;
    const size_t width = sizeof(uint64_t);

    const uint64_t initial_contents[] = {10, 20, 30, 50};
    const uint64_t element = 40;

    const size_t count = sizeof(initial_contents) / width;

    mu_assert("Could not initialize ArrayList", initialize_array_list(&list, capacity, width) == NULL);

    mu_assert("Error while adding all the elements to the list.", add_all_to_array_list(&list, initial_contents, count) == NULL);
    mu_assert("Error while inserting element into the list.", insert_in_array_list(&list, 3, &element) == NULL);

    mu_assert("Could not delete data properly.", delete_index_array_list(&list, 4) == NULL);

    filename = "insertion_and_deletion.tmp";

    temp_file = fopen(filename, "w");

    if (!temp_file)
    {
        return "Could not open temporary file for writing data.";
    }

    mu_assert("Failed to write the list's data to file.", output_array_list(temp_file, &list, print_uint64_t) == NULL);

    fclose(temp_file);

    temp_file = fopen(filename, "r");

    if (!temp_file)
    {
        return "Could not open temporary file for reading data.";
    }

    for (size_t index = 0; index < count; index++)
    {
        size_t index_data;
        uint64_t data;
        uint64_t real_data = 10 * (index + 1);
        fscanf(temp_file, "%" SCNuMAX ": %" SCNu64 "\n", &index_data, &data);
        mu_assert("Invalid index.", index_data == index);
        mu_assert("Invalid data.", data == real_data);
    }

    fclose(temp_file);
    remove_file(filename);

    mu_assert("Could not deallocate ArrayList", free_array_list(&list) == NULL);
    return NULL;
}

static void print_uint8_t(FILE *out_stream, const size_t index, const void *element)
{
    fprintf(out_stream, "%" PRIuMAX ": %" PRIu16 "\n", index, *((uint8_t *)element));
}

static char *set_and_get_work()
{
    ArrayList list = {};
    const size_t capacity = 5;
    const size_t width = sizeof(uint8_t);

    const uint8_t initial_contents[] = {121, 122, 123, 134, 125};
    const uint8_t element = 124;

    const size_t count = sizeof(initial_contents) / width;
    const size_t set_idx = 3, get_idx = 4;

    mu_assert("Could not initialize ArrayList", initialize_array_list(&list, capacity, width) == NULL);

    mu_assert("Error while adding all the elements to the list.", add_all_to_array_list(&list, initial_contents, count) == NULL);
    mu_assert("Error while setting an element of the list.", set_in_array_list(&list, set_idx, &element) == NULL);

    uint8_t result;
    mu_assert("Error while trying to obtain data from ArrayList.", get_from_array_list(&list, get_idx, (void *)&result) == NULL);

    mu_assert("Value obtained did not match.", result == initial_contents[get_idx]);

    filename = "set_and_get.tmp";

    temp_file = fopen(filename, "w");

    if (!temp_file)
    {
        return "Could not open temporary file for writing data.";
    }

    mu_assert("Failed to write the list's data to file.", output_array_list(temp_file, &list, print_uint8_t) == NULL);

    fclose(temp_file);

    temp_file = fopen(filename, "r");

    if (!temp_file)
    {
        return "Could not open temporary file for reading data.";
    }

    for (size_t index = 0; index < count; index++)
    {
        size_t index_data;
        uint16_t data;
        uint8_t real_data = 121 + index;
        fscanf(temp_file, "%" SCNuMAX ": %" SCNu16 "\n", &index_data, &data);
        mu_assert("Invalid index.", index_data == index);
        mu_assert("Invalid data.", data == real_data);
    }

    fclose(temp_file);
    remove_file(filename);

    mu_assert("Could not deallocate ArrayList", free_array_list(&list) == NULL);
    return NULL;
}

static int target;

static bool is_target(void *element)
{
    return *((int *)element) == target;
}

static const int cmp_ints(const void *a, const void *b)
{
    int iA = *((int *)a);
    int iB = *((int *)b);
    return (iA > iB) - (iA < iB);
}

static char *search_and_comparison_work()
{
    ArrayList list1 = {};
    ArrayList list2 = {};

    const size_t capacity = 5;
    const size_t width = sizeof(int);

    mu_assert("Could not initialize arraylist 1.",
              initialize_array_list(&list1, capacity, width) == NULL);
    mu_assert("Could not initialize arraylist 2.",
              initialize_array_list(&list2, capacity, width) == NULL);

    const int elements[] = {98, 65, 46, 89};
    const size_t count = sizeof(elements) / width;
    const int new_element1 = 101;
    const int new_element2 = 102;

    mu_assert("Failed to add elements to arraylist 1.",
              add_all_to_array_list(&list1, elements, count) == NULL);
    mu_assert("Failed to add elements to arraylist 2.",
              add_all_to_array_list(&list2, elements, count) == NULL);

    size_t location;
    size_t answer = 2;
    target = 10;

    mu_assert("Search should have been unsuccessful.",
              strcmp(search_array_list(&list1, &location, is_target), "Search unsuccessful") == 0);
    target = elements[answer];
    mu_assert("Search should have been successful.",
              search_array_list(&list1, &location, is_target) == NULL);

    mu_assert("Invalid search result.", location == answer);

    mu_assert("Could not append additional element to list 2.",
              append_to_array_list(&list2, &new_element2) == NULL);

    mu_assert("ArrayLists detectected as equal, while they are not.",
              compare_array_lists(&list1, &list2, cmp_ints) < 0);

    mu_assert("Could not append additional element to list 1.",
              append_to_array_list(&list1, &new_element1) == NULL);

    mu_assert("ArrayLists detectected as equal, while they are not.",
              compare_array_lists(&list1, &list2, cmp_ints) < 0);

    mu_assert("Could not insert element in arraylist 1.",
              set_in_array_list(&list1, count, &new_element2) == NULL);

    mu_assert("ArrayLists should have been equal but they are not.",
              compare_array_lists(&list1, &list2, cmp_ints) == 0);

    mu_assert("Could not deallocate arraylist 1.", free_array_list(&list1) == NULL);
    mu_assert("Could not deallocate arraylist 2.", free_array_list(&list2) == NULL);

    return NULL;
}

static char *operate_on_int(void *result, const size_t index, const void *element)
{
    double *dbl_pointer = (double *)result;
    *dbl_pointer += *((int *)element);
    return NULL;
}

static char *average_calculation_works()
{
    int elements[100];
    const size_t width = sizeof(int);
    const size_t size = sizeof(elements) / width;

    double actual_result = 0.0;
    for (size_t index = 0; index < size; index++)
    {
        elements[index] = 10 * (index + 1);
        actual_result += elements[index];
    }
    actual_result /= size;

    // Now perform the summation using an ArrayList
    ArrayList list = {};
    mu_assert("Could not initialize array list.", initialize_array_list(&list, size, width) == NULL);
    mu_assert("Could not add elements to the array list.", add_all_to_array_list(&list, elements, size) == NULL);

    double result = 0.0;
    mu_assert("Error while applying function to the elements.",
              apply_to_array_list(&list, &result, operate_on_int) == NULL);
    result /= size;

    mu_assert("The results (averages) do not match.", result == actual_result);

    mu_assert("Error while freeing memory.", free_array_list(&list) == NULL);
    return NULL;
}

static char *all_tests()
{
    mu_run_test(empty_array_list_test);
    mu_run_test(addition_to_list_works);
    mu_run_test(output_works_correctly);
    mu_run_test(insertion_and_deletion_work);
    mu_run_test(set_and_get_work);
    mu_run_test(search_and_comparison_work);
    mu_run_test(average_calculation_works);
    return NULL;
}

int main(int argc, char const *argv[])
{
    char *result = all_tests();
    if (result != 0)
    {
        // It might be possible that a few files were not closed due to
        // a failed test. Close them here.
        if (temp_file)
        {
            fclose(temp_file);
        }
        remove(filename);
        printf("%s\n", result);
    }
    else
    {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);

    return result != 0;
}
