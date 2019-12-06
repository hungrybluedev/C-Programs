/**
 * Methods to declare panic when things go wrong and you don't want
 * to handle them and rather have the program stop gracefully(?).
 */

#include <stdio.h>

/**
 * This method can be called when an unrecoverable error occurs and
 * you don't want to deal with it. Essentially, this method outputs
 * an error message supplied the calling code and ends the execution
 * with a status code that implies failure (EXIT_FAILURE).
 *
 * @param output  The file to output the panic message to.
 * @param message The message to display when panicking.
 */
void panic(FILE *output, const char *message);