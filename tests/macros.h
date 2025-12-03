/**
 * Macros used for testing.
 */
#ifndef testing_macros_h
#define testing_macros_h

#include <assert.h>

#define RUN_TEST(x)                          \
    do {                                     \
        fprintf(stderr, "RUNNING " #x "\n"); \
        (x)();                               \
        fprintf(stderr, #x " PASSED\n");     \
    } while (0)

#define ASSERT(x)                                      \
    do {                                               \
        fprintf(stderr, "TESTING CONDITION " #x "\n"); \
        assert(x);                                     \
    } while (0)

#endif
