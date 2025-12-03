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
    size_t length = strlen(raw_str) - 1;
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
 * @brief convert a constring to a char pointer
 */
static char* constring_to_char(constring cstr)
{
    char* dest_string = (char*)malloc(cstr.length + 2);
    snprintf(dest_string, cstr.length + 2, "%s", cstr.raw);
    dest_string[cstr.length + 2] = '\0';
    return dest_string;
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
    size_t j = 0;
    while (i >= 0 && isspace(cstr.raw[i])) {
        i = i - 1;
        j = j + 1;
    }
    size_t new_len = cstr.length - j;
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

static bool constring_is_empty(constring cstr)
{
    return cstr.length == 0;
}

/**
 * @brief split a constring at `at`.
 * @returns `constring** retval`, where `retval[0]` is the first element and `retval[1]` is the second element. `retval == NULL` whenever there is an error.
 */
static constring** constring_split_at(constring cstr, size_t at)
{
    // check if it goes over the length
    if (at > cstr.length)
        return NULL;

    // initialize the return value
    constring** retval = (constring**)malloc(sizeof(constring*) * 2);
    retval[0] = NULL;
    retval[1] = NULL;

    // TODO(hanleyc01): these two branches probably should be marked unlikely; later optimization if it actually changes anything
    if (at == cstr.length) {
        constring* new_cstr = (constring*)malloc(sizeof(constring));
        new_cstr->length = cstr.length;
        new_cstr->raw = cstr.raw;
        retval[0] = new_cstr;
        return retval;
    } else if (at == 0) {
        constring* new_cstr = (constring*)malloc(sizeof(constring));
        new_cstr->length = cstr.length;
        new_cstr->raw = cstr.raw;
        retval[1] = new_cstr;
        return retval;
    } else {
        size_t fst_length = at - 1;
        const char* fst_ptr = cstr.raw;
        constring* fst = (constring*)malloc(sizeof(constring));
        fst->length = fst_length;
        fst->raw = cstr.raw;

        size_t snd_length = cstr.length - at;
        const char* snd_ptr = cstr.raw + at;
        constring* snd = (constring*)malloc(sizeof(constring));
        snd->length = snd_length;
        snd->raw = snd_ptr;

        retval[0] = fst;
        retval[1] = snd;
        return retval;
    }
}

#endif
