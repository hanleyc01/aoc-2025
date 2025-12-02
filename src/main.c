#include "file_io.h"
#include <stdio.h>

int main(void)
{
    const char* day1_test_path = "./data/day1/test.txt";
    struct file* f = file_open(day1_test_path, "rb");

    if (f == NULL) {
        fprintf(stderr, "ERROR: FILE %s DOES NOT EXIST\n", day1_test_path);
        return -1;
    }

    int err = 0;
    size_t file_length = 0;

    const char* file_contents = file_read(f, &err, &file_length);

    if (file_contents == NULL) {
        switch (err) {
        case FILE_NOT_EXIST:
            fprintf(stderr, "ERROR: FILE DOES NOT EXIST\n");
            return -1;
        case FILE_TOO_LARGE:
            fprintf(stderr, "ERROR: FILE TOO LARGE TO READ\n");
            return -1;
        case FILE_READ_ERROR:
            fprintf(stderr, "ERROR: FILE READ ERROR\n");
            return -1;
        }
    }

    printf("read %zu bytes\n", file_length);
    printf("%s\n", file_contents);

    file_close(f);

    return 0;
}
