#ifndef aoc_2025_fileio_h
#define aoc_2025_fileio_h

#include <stdio.h>
#include <stdlib.h>

#define FILE_OK 0
#define FILE_NOT_EXIST 1
#define FILE_TOO_LARGE 2
#define FILE_READ_ERROR 3

#define FILEIO_MAX_FILE_SIZE 1073741824

/**
 * @brief Contemporary File IO operations. Common and useful
 * operations that I hate writing over and over again.
 */
struct file {
    FILE* raw_file; /**< Reference to a file */
};

/**
 * @brief Open a file
 * @param file_path A string which is the path to the file that you wish to open.
 * @param read_mode The read mode that you want, see Python `open` documentation for the different
 * modes.
 * @return A `struct file *`. `NULL` if the file does not exist. Note that failure does not allocate any memory.
 */
static struct file* file_open(const char* file_path, const char* read_mode)
{
    FILE* raw_file = fopen(file_path, read_mode);
    if (raw_file == NULL)
        return NULL;

    struct file* f = (struct file*)malloc(sizeof(struct file));
    f->raw_file = raw_file;
    return f;
}

/**
 * @brief Close a file and free it.
 * @param file The file to close.
 */
static void file_close(struct file* file)
{
    fclose(file->raw_file);
    free(file);
}

/**
 * @brief Read a file to a string.
 * @param file The file to read.
 * @param err Error code.
 * @param file_size The size of the file that is set by the function.
 * @return Pointer to the file that is read, `NULL` if the read fails. See `err` if `NULL`.
 */
static char* file_read(struct file* file, int* err, size_t* file_size)
{
    fseek(file->raw_file, 0, SEEK_END);
    size_t length = ftell(file->raw_file);
    fseek(file->raw_file, 0, SEEK_SET);

    if (length > FILEIO_MAX_FILE_SIZE) {
        *err = FILE_TOO_LARGE;

        return NULL;
    }

    char* buffer = (char*)malloc(length + 1);

    if (length) {
        size_t read_length = fread(buffer, 1, length, file->raw_file);

        if (length != read_length) {
            free(buffer);
            *err = FILE_READ_ERROR;
            return NULL;
        }
    }

    buffer[length] = '\0';
    *file_size = length;
    return buffer;
}

#endif
