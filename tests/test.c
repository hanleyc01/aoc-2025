#include <stdio.h>

#include "test_constring.h"
#include "test_file_io.h"

int main(void)
{
    fprintf(stderr, "BEGINNING UNIT TESTS\n");

    fprintf(stderr, "TESTING file_io\n");
    test_file_io();
    fprintf(stderr, "TESTING constring\n");
    test_constring();

    return 0;
}
