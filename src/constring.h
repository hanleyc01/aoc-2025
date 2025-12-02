/**
 * `constring`, or, Connor strings.
 *
 * String operations that are common, and should be included in a `c` stdlib,
 * but aren't.
 *
 * I don't like rewriting either: so here we go.
 */
#ifndef aoc_2025_constring_h
#define aoc_2025_constring_h

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <assert.h>

#define constring_maxlen 1073741824

/**
 * @brief String wrapper and methods.
 */
typedef struct
{
    size_t length;
    const char* raw;
} constring;

/**
 * @brief allocate a new constring from a raw string literal.
 * @param raw_str The null-terminated raw string literal.
 * @return A constring.
 */
static constring constring_from_char(const char* raw_str)
{
    size_t length = strnlen(raw_str, constring_maxlen);
    constring str = {
        .length = length,
        .raw = raw_str,
    };
    return str;
}

/**
 * @brief allocate a new constring from a raw string literal taking `n` bytes.
 * @param raw_str The raw string literal
 * @param n The number of bytes
 * @return A constring.
 */
static constring constring_from_char_n(const char* raw_str, size_t n)
{
    return (constring) {
        .length = n,
        .raw = raw_str,
    };
}

/**
 * Trim leading whitespace.
 */
static constring constring_trim_leading(constring cstr)
{
    // Iterate from beginning till no more whitespace.
    size_t i = 0;
    const char* new_raw = cstr.raw;
    while (i < cstr.length && isspace(cstr.raw[i])) {
        i = i + 1;
        new_raw += 1;
    }

    size_t new_length = cstr.length - i;
    return (constring) {
        .length = new_length,
        .raw = new_raw,
    };
}

/**
 * @brief Trim trailing whitespace.
 */
static constring constring_trim_trailing(constring cstr)
{
    size_t i = cstr.length;
    while (i >= 0 && isspace(cstr.raw[i]))
        i--;
    size_t new_len = cstr.length - i;
    return (constring) {
        .length = new_len,
        .raw = cstr.raw,
    };
}

/**
 * @brief Trim a constring of leading and trailing whitespace.
 */
static constring constring_trim(constring cstr)
{
    constring trimmed_leading = constring_trim_leading(cstr);
    constring trimmed = constring_trim_trailing(trimmed_leading);
    return trimmed;
}

/**
 * @brief convert a constring to a char pointer
 */
static char* constring_to_char(constring cstr)
{
    if (cstr.length == 0)
        return "";
    char* dest_string = (char*)malloc(cstr.length + 1);
    snprintf(dest_string, cstr.length + 1, "%s", cstr.raw);
    dest_string[cstr.length] = '\0';
    return dest_string;
}

static bool constring_is_empty(constring cstr)
{
    return cstr.length == 0;
}

#endif
