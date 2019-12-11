#ifndef C_PROGRAMS_TEST_H
#define C_PROGRAMS_TEST_H

#include <stdlib.h>
/**
 * Minimal testing framework inspired by John Brewer's <jera.com> minunit.
 *
 * The link to the original program:
 * http://www.jera.com/techinfo/jtns/jtn002.html.
 *
 *
 */
#define mu_assert(message, test) \
    do                           \
    {                            \
        if (!(test))             \
            return message;      \
    } while (0)

#define mu_run_test(test)       \
    do                          \
    {                           \
        char *message = test(); \
        tests_run++;            \
        test_count++;           \
        if (!message)           \
            tests_passed++;     \
        else                    \
            return message;     \
    } while (0)



extern size_t test_count;
extern size_t tests_passed;
extern size_t tests_run;


#endif // C_PROGRAMS_TEST_H
