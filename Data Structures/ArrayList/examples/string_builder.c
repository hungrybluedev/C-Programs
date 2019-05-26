#include <stdio.h>
#include <stdlib.h>

#include "../list.h"

int main()
{
    ArrayList chars = {};
    const size_t initial_capacity = 128;
    char *result = initialize_array_list(&chars, initial_capacity, sizeof(char));

    if (result)
    {
        perror("Could not initialize the ArrayList.\n");
        return EXIT_FAILURE;
    }

    const char END_OF_STRING = '\0';
    int ch = getchar();

    while (ch != EOF)
    {
        result = append_to_array_list(&chars, &ch);
        if (result)
        {
            perror("Failed to add character to Array List.\n");
            return EXIT_FAILURE;
        }

        ch = getchar();
    }
    result = append_to_array_list(&chars, &END_OF_STRING);
    if (result)
    {
        perror("Failed to add character to Array List.\n");
        return EXIT_FAILURE;
    }

    printf("The string read was:\n\n%s\n", LIST_DATA(&chars));

    result = free_array_list(&chars);

    if (result)
    {
        perror("Could not deallocate the ArrayList.\n");
        return EXIT_FAILURE;
    }

    return result != NULL;
}