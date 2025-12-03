/**
 * Testing for constring.h
 */
#ifndef test_constring_h
#define test_constring_h

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "macros.h"

#include "../src/constring.h"

static void test_constring_from()
{
    const char* test_str = "hello, world!";
    constring cstr = constring_from_char(test_str);
    size_t test_len = strlen(test_str) - 1;
    ASSERT(cstr.length == test_len);
    ASSERT(cstr.raw == test_str);
}

static void test_constring_to_char()
{
    const char* test = "hello, world!";
    constring cstr = constring_from_char(test);

    char* newstr = constring_to_char(cstr);
    ASSERT(strcmp(newstr, test) == 0);
    free(newstr);
}

static void test_constring_trim_leading()
{
    const char* test_leading_ws = " hello, world!";
    constring leading_ws_cstr = constring_from_char(test_leading_ws);
    constring trimmed_cstr = constring_trim_leading(leading_ws_cstr);

    char* trimmed_str = constring_to_char(trimmed_cstr);
    ASSERT(strcmp(trimmed_str, "hello, world!") == 0);

    free(trimmed_str);
}

static void test_constring_trim_trailing()
{
    const char* test_leading_ws = "hello, world!  ";
    constring leading_ws_cstr = constring_from_char(test_leading_ws);
    constring trimmed_cstr = constring_trim_trailing(leading_ws_cstr);

    char* trimmed_str = constring_to_char(trimmed_cstr);
    ASSERT(strcmp(trimmed_str, "hello, world!") == 0);
    free(trimmed_str);
}

static void test_constring_trim()
{
    const char* test_leading_ws = "\n   hello, world! \n  ";
    constring leading_ws_cstr = constring_from_char(test_leading_ws);
    constring trimmed_cstr = constring_trim(leading_ws_cstr);

    char* trimmed_str = constring_to_char(trimmed_cstr);
    ASSERT(strcmp(trimmed_str, "hello, world!") == 0);
    free(trimmed_str);
}

static void test_constring_trim_empty()
{
    const char* test_leading_ws = "\n\n";
    constring leading_ws_cstr = constring_from_char(test_leading_ws);
    constring trimmed_cstr = constring_trim(leading_ws_cstr);

    char* trimmed_str = constring_to_char(trimmed_cstr);
    ASSERT(strcmp(trimmed_str, "") == 0);
    free(trimmed_str);
}

static void test_constring_split()
{
    const char* test_leading_ws = "hello, world!";
    constring test_cstr = constring_from_char(test_leading_ws);
    constring** splitten = constring_split_at(test_cstr, 7);

    constring* lhs = splitten[0];
    constring* rhs = splitten[1];

    ASSERT(lhs != NULL);
    ASSERT(rhs != NULL);

    const char* lhs_str = constring_to_char(*lhs);
    const char* rhs_str = constring_to_char(*rhs);

    fprintf(stderr, "lhs_str: `%s`\n", lhs_str);
    fprintf(stderr, "rhs_str: `%s`\n", rhs_str);

    ASSERT(strcmp(lhs_str, "hello, ") == 0);
    ASSERT(strcmp(rhs_str, "world!") == 0);

    free((void*)lhs_str);
    free((void*)rhs_str);
    free(lhs);
    free(rhs);
    free(splitten);
}

static void test_constring(void)
{
    RUN_TEST(test_constring_from);
    RUN_TEST(test_constring_to_char);
    RUN_TEST(test_constring_trim_leading);
    RUN_TEST(test_constring_trim_trailing);
    RUN_TEST(test_constring_trim);
    RUN_TEST(test_constring_trim_empty);
    RUN_TEST(test_constring_split);
}

#endif
