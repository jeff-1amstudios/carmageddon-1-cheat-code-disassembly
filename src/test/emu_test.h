////////////////////////////////////////////////////////////////////////////////
////  Extended MinUnit - a minimalist unit testing framework for C and C++  ////
////////////////////////////////////////////////////////////////////////////////
/* MIT License
 *
 * Copyright (c) 2017-2018, Victor Cushman
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#ifndef _EMUTEST_H_
#define _EMUTEST_H_

#define EMU_VERSION_MAJOR_STR "2"
#define EMU_VERSION_MINOR_STR "0"
#define EMU_VERSION_PATCH_STR "0"
#define EMU_VERSION_STR EMU_VERSION_MAJOR "."                                  \
                        EMU_VERSION_MINOR "."                                  \
                        EMU_VERSION_PATCH

#include <inttypes.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>

#ifdef __GNUC__
#   pragma GCC system_header
#elif __clang__
#   pragma clang system_header
#endif

// USER SETTINGS
#ifdef _EMU_DISABLE_LOGGING_
#   define _EMU_SETTING_LOGGING_ENABLED 0
#else
#   define _EMU_SETTING_LOGGING_ENABLED 1
#endif // !_EMU_DISABLE_LOGGING_

#ifdef _EMU_ENABLE_COLOR_
#   define _EMU_SETTING_COLOR_ENABLED 1
#else
#   define _EMU_SETTING_COLOR_ENABLED 0
#endif // !_EMU_ENABLE_COLOR_

////////////////////////////////////////////////////////////////////////////////
//// BEHIND THE SCENES VOODOO MAGIC ////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// MISC CONSTANTS //////////////////////////////////////////////////////////////
#define _EMU_TEST_SUCCESS 0
#define _EMU_TEST_FAILURE 1
#define _EMU_NULL 0
#define _EMU_EXPECT_TMPLT 0
#define _EMU_ASSERT_TMPLT 1
#define _EMU_DBL_DIG 17 // Maximum digits in a double using IEEE-754 floating
                        // point standard.

// HELPER MACROS ///////////////////////////////////////////////////////////////
#define _EMU_STRINGIFY_HELPER(x) #x
#define _EMU_STRINGIFY(x) _EMU_STRINGIFY_HELPER(x)

#define _EMU_IS_EQ(a, b) ((a) == (b))
#define _EMU_IS_GT(a, b) ((a) >  (b))
#define _EMU_IS_GE(a, b) ((a) >= (b))
#define _EMU_IS_LT(a, b) ((a) <  (b))
#define _EMU_IS_LE(a, b) ((a) <= (b))
#define _EMU_IS_NULL(expr) ((expr) == _EMU_NULL)
#define _EMU_IS_ELEMENT_EQ(a, b) ((a)[_EMU_INDEX] == (b)[_EMU_INDEX])
#define _EMU_CONT_ITERATE_STRING(a, b)                                         \
    ((a)[_EMU_INDEX] != '\0' && (b)[_EMU_INDEX] != '\0')
#define _EMU_IS_FEQ(a, b, epsilon) (fabs((a) - (b)) < epsilon)

#define _EMU_SET_CACHED_CHAR(a, b)                                             \
    _EMU_CACHED_CHAR[0] = (a);                                                 \
    _EMU_CACHED_CHAR[1] = (b);
#define _EMU_SET_CACHED_INT(a, b)                                              \
    _EMU_CACHED_INT[0] = (a);                                                  \
    _EMU_CACHED_INT[1] = (b);
#define _EMU_SET_CACHED_UINT(a, b)                                             \
    _EMU_CACHED_UINT[0] = (a);                                                 \
    _EMU_CACHED_UINT[1] = (b);
#define _EMU_SET_CACHED_FLOAT(a, b)                                            \
    _EMU_CACHED_FLOAT[0] = (a);                                                \
    _EMU_CACHED_FLOAT[1] = (b);

#ifdef __clang__
#   define _EMU_DIAGNOSTIC_PUSH _Pragma("clang diagnostic push")
#   define _EMU_DIAGNOSTIC_POP  _Pragma("clang diagnostic pop")
#   define _EMU_DIAGNOSTIC_DISABLE_WARN_UNUSED_VARIABLE                        \
        _Pragma("clang diagnostic ignored \"-Wunused-variable\"")
#elif __GNUC__
#   define _EMU_DIAGNOSTIC_PUSH _Pragma("GCC diagnostic push")
#   define _EMU_DIAGNOSTIC_POP  _Pragma("GCC diagnostic pop")
#   define _EMU_DIAGNOSTIC_DISABLE_WARN_UNUSED_VARIABLE                        \
        _Pragma("GCC diagnostic ignored \"-Wunused-variable\"")
#else
#   define _EMU_DIAGNOSTIC_PUSH /* nothing */
#   define _EMU_DIAGNOSTIC_POP  /* nothing */
#   define _EMU_DIAGNOSTIC_DISABLE_WARN_UNUSED_VARIABLE /* nothing */
#endif

// LOGGING /////////////////////////////////////////////////////////////////////
#define _EMU_LOG_STR_INDENT_BAR   "| "
#define _EMU_LOG_STR_INDENT_NOBAR "  "
#define _EMU_LOG_STR_TEST         "[TEST      ]"
#define _EMU_LOG_STR_GROUP        "[GROUP     ]"
#define _EMU_LOG_STR_TEST_PASS    "TEST  PASS"
#define _EMU_LOG_STR_TEST_FAIL    "TEST  FAIL"
#define _EMU_LOG_STR_GROUP_PASS   "GROUP PASS"
#define _EMU_LOG_STR_GROUP_FAIL   "GROUP FAIL"
#define _EMU_LOG_STR_FILE         "FILE = " _EMU_STRINGIFY(__FILE__)
#define _EMU_LOG_STR_LINE         "LINE = " _EMU_STRINGIFY(__LINE__)

#define _EMU_LOG_STR_EXPECTED " expected "
#define _EMU_LOG_STR_EQ       " to equal "
#define _EMU_LOG_STR_NE       " to not equal "
#define _EMU_LOG_STR_GT       " to be greater than "
#define _EMU_LOG_STR_GE       " to be greater than or equal to "
#define _EMU_LOG_STR_LT       " to be less than "
#define _EMU_LOG_STR_LE       " to be less than or equal to "
#define _EMU_LOG_STR_EXCEPT   "exception "

#define _EMU_ANSI_ESC_DEFAULT "\x1B[0m"
#define _EMU_ANSI_ESC_RED     "\x1B[31m"
#define _EMU_ANSI_ESC_GREEN   "\x1B[32m"

#define _EMU_SET_COLOR(color) printf(color)
#define _EMU_RESET_COLOR()    printf(_EMU_ANSI_ESC_DEFAULT)

#define _EMU_LOG_GENERIC_FAILURE() printf("\n")

#define _EMU_LOG_CHAR_FAILURE(a, b, relation_str)                              \
printf(_EMU_LOG_STR_EXPECTED "\'%c\'" relation_str "\'%c\'\n",                 \
    (char)a, (char)b)

#define _EMU_LOG_INT_FAILURE(a, b, relation_str)                               \
printf(_EMU_LOG_STR_EXPECTED "%lld" relation_str "%lld\n",                     \
    (long long signed)a, (long long signed)b)

#define _EMU_LOG_UINT_FAILURE(a, b, relation_str)                              \
printf(_EMU_LOG_STR_EXPECTED "%llu" relation_str "%llu\n",                     \
    (long long unsigned)a, (long long unsigned)b)

#define _EMU_LOG_FLOAT_FAILURE(a, b, relation_str)                             \
printf(_EMU_LOG_STR_EXPECTED "%.*e" relation_str "%.*e\n",                     \
    _EMU_DBL_DIG - 1, (double)a, _EMU_DBL_DIG - 1, (double)b)

#ifdef __cplusplus
#define _EMU_LOG_EXCEPTION_FAILURE(exception)                                  \
printf(_EMU_LOG_STR_EXPECTED _EMU_LOG_STR_EXCEPT                               \
    _EMU_STRINGIFY(exception) "\n");
#endif // !__cplusplus

#define _EMU_PRINT_FAILURE(failure_type, failure_printf)                       \
for (int i = 0; i < emu_indent; ++i){printf(_EMU_LOG_STR_INDENT_BAR);}         \
printf(_EMU_LOG_STR_INDENT_BAR failure_type " FAILURE:");                      \
failure_printf;                                                                \
for (int i = 0; i < emu_indent; ++i){printf(_EMU_LOG_STR_INDENT_BAR);}         \
printf(                                                                        \
    _EMU_LOG_STR_INDENT_BAR _EMU_LOG_STR_INDENT_NOBAR "%s\n",                  \
    _EMU_LOG_STR_FILE                                                          \
);                                                                             \
for (int i = 0; i < emu_indent; ++i){printf(_EMU_LOG_STR_INDENT_BAR);}         \
printf(                                                                        \
    _EMU_LOG_STR_INDENT_BAR _EMU_LOG_STR_INDENT_NOBAR "%s\n",                  \
    _EMU_LOG_STR_LINE                                                          \
)

#define _EMU_PRINT_TEST_BEGIN()                                                \
for (int i = 0; i < emu_indent; ++i){printf(_EMU_LOG_STR_INDENT_BAR);}         \
printf(_EMU_LOG_STR_TEST " ---> %s\n", _EMU_TEST_NAME)

#define _EMU_PRINT_TEST_END()                                                  \
for (int i = 0; i < emu_indent; ++i){printf(_EMU_LOG_STR_INDENT_BAR);}         \
printf("[");                                                                   \
if (_EMU_TEST_RESULT == _EMU_TEST_SUCCESS)                                     \
{                                                                              \
    if (emu_color_enabled){_EMU_SET_COLOR(_EMU_ANSI_ESC_GREEN);}               \
    printf(_EMU_LOG_STR_TEST_PASS);                                            \
}                                                                              \
else                                                                           \
{                                                                              \
    if (emu_color_enabled){_EMU_SET_COLOR(_EMU_ANSI_ESC_RED);}                 \
    printf(_EMU_LOG_STR_TEST_FAIL);                                            \
}                                                                              \
if (emu_color_enabled){_EMU_RESET_COLOR();}                                    \
printf("]\n");                                                                 \

#define _EMU_PRINT_GROUP_BEGIN()                                               \
for (int i = 0; i < emu_indent; ++i){printf(_EMU_LOG_STR_INDENT_BAR);}         \
printf(_EMU_LOG_STR_GROUP " ===> %s\n", _EMU_GROUP_NAME)

#define _EMU_PRINT_GROUP_END()                                                 \
for (int i = 0; i < emu_indent; ++i){printf(_EMU_LOG_STR_INDENT_BAR);}         \
putchar('[');                                                                  \
if (_EMU_FAILED_TESTS == 0)                                                    \
{                                                                              \
    if (emu_color_enabled){_EMU_SET_COLOR(_EMU_ANSI_ESC_GREEN);}               \
    printf(_EMU_LOG_STR_GROUP_PASS);                                           \
}                                                                              \
else                                                                           \
{                                                                              \
    if (emu_color_enabled){_EMU_SET_COLOR(_EMU_ANSI_ESC_RED);}                 \
    printf(_EMU_LOG_STR_GROUP_FAIL);                                           \
}                                                                              \
if (emu_color_enabled){_EMU_RESET_COLOR();}                                    \
printf("]\n");                                                                 \

#define _EMU_GOTO_END_TEST_IF_ASSERT(is_assert)                                \
if(is_assert){goto _emu_label_end_test;}

// TEMPLATES FOR GENERATING TOOL CODE //////////////////////////////////////////
// single comparisons
#define _EMU_COND_TEMPLATE(                                                    \
    is_assert,                                                                 \
    pass_cond,                                                                 \
    failure_type,                                                              \
    failure_printf                                                             \
)                                                                              \
do                                                                             \
{                                                                              \
    if (!pass_cond)                                                            \
    {                                                                          \
        _EMU_TEST_RESULT = _EMU_TEST_FAILURE;                                  \
        if (emu_logging_enabled)                                               \
        {                                                                      \
            _EMU_PRINT_FAILURE(failure_type, failure_printf);                  \
        }                                                                      \
        _EMU_GOTO_END_TEST_IF_ASSERT(is_assert);                               \
    }                                                                          \
} while (0)

// exceptions (C++ only)
#ifdef __cplusplus
#define _EMU_THROW_TEMPLATE(                                                   \
    is_assert,                                                                 \
    expr,                                                                      \
    failure_type                                                               \
)                                                                              \
do                                                                             \
{                                                                              \
    try                                                                        \
    {                                                                          \
        expr;                                                                  \
        _EMU_TEST_RESULT = _EMU_TEST_FAILURE;                                  \
        if (emu_logging_enabled)                                               \
        {                                                                      \
            _EMU_PRINT_FAILURE(failure_type, _EMU_LOG_GENERIC_FAILURE());      \
        }                                                                      \
    }                                                                          \
    catch (...) {}                                                             \
} while (0)

#define _EMU_THROW_TYPE_TEMPLATE(                                              \
    is_assert,                                                                 \
    expr,                                                                      \
    exception,                                                                 \
    failure_type,                                                              \
    failure_printf                                                             \
)                                                                              \
do                                                                             \
{                                                                              \
    try                                                                        \
    {                                                                          \
        expr;                                                                  \
        _EMU_TEST_RESULT = _EMU_TEST_FAILURE;                                  \
        if (emu_logging_enabled)                                               \
        {                                                                      \
            _EMU_PRINT_FAILURE(failure_type, failure_printf);                  \
        }                                                                      \
        _EMU_GOTO_END_TEST_IF_ASSERT(is_assert);                               \
    }                                                                          \
    catch (exception e) {}                                                     \
    catch (...)                                                                \
    {                                                                          \
        _EMU_TEST_RESULT = _EMU_TEST_FAILURE;                                  \
        if (emu_logging_enabled)                                               \
        {                                                                      \
            _EMU_PRINT_FAILURE(failure_type, failure_printf);                  \
        }                                                                      \
        _EMU_GOTO_END_TEST_IF_ASSERT(is_assert);                               \
    }                                                                          \
} while (0)

#define _EMU_NO_THROW_TEMPLATE(                                                \
    is_assert,                                                                 \
    expr,                                                                      \
    failure_type                                                               \
)                                                                              \
do                                                                             \
{                                                                              \
    try                                                                        \
    {                                                                          \
        expr;                                                                  \
    }                                                                          \
    catch (...)                                                                \
    {                                                                          \
        _EMU_TEST_RESULT = _EMU_TEST_FAILURE;                                  \
        if (emu_logging_enabled)                                               \
        {                                                                      \
            _EMU_PRINT_FAILURE(failure_type, _EMU_LOG_GENERIC_FAILURE());      \
        }                                                                      \
        _EMU_GOTO_END_TEST_IF_ASSERT(is_assert);                               \
    }                                                                          \
} while (0)
#endif // !__cplusplus

////////////////////////////////////////////////////////////////////////////////
//// "PUBLIC" MACROS ///////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// TEST/GROUP DEFINITION AND EXECUTION MACROS //////////////////////////////////
#define EMU_TEST(name)                                                         \
int _EMU_TEST_##name(                                                          \
    int emu_logging_enabled,                                                   \
    int emu_color_enabled,                                                     \
    int emu_indent                                                             \
)                                                                              \
{ /* actual opening bracket */                                                 \
_EMU_DIAGNOSTIC_PUSH                                                           \
_EMU_DIAGNOSTIC_DISABLE_WARN_UNUSED_VARIABLE                                   \
    char const* const _EMU_TEST_NAME = _EMU_STRINGIFY(name);                   \
    int _EMU_TEST_RESULT = _EMU_TEST_SUCCESS;                                  \
    char     _EMU_CACHED_CHAR[2];                                              \
    int64_t  _EMU_CACHED_INT[2];                                               \
    uint64_t _EMU_CACHED_UINT[2];                                              \
    double   _EMU_CACHED_FLOAT[2];                                             \
_EMU_DIAGNOSTIC_POP                                                            \
    if (emu_logging_enabled){_EMU_PRINT_TEST_BEGIN();}                         \

#define EMU_END_TEST()                                                         \
    } /* match user's opening bracket */                                       \
    goto _emu_label_end_test; /* goto used to disable unused label warnings */ \
_emu_label_end_test:                                                           \
    if (emu_logging_enabled){_EMU_PRINT_TEST_END();}                           \
    return _EMU_TEST_RESULT;                                                   \

#define EMU_GROUP(name)                                                        \
int _EMU_TEST_##name(                                                          \
    int emu_logging_enabled,                                                   \
    int emu_color_enabled,                                                     \
    int emu_indent                                                             \
)                                                                              \
{ /* actual opening bracket */                                                 \
    char const* const _EMU_GROUP_NAME = _EMU_STRINGIFY(name);                  \
    int _EMU_FAILED_TESTS = 0;                                                 \
    if (emu_logging_enabled){_EMU_PRINT_GROUP_BEGIN();}                        \

#define EMU_END_GROUP()                                                        \
    } /* match user's opening bracket */                                       \
    if (emu_logging_enabled){_EMU_PRINT_GROUP_END();}                          \
    return _EMU_FAILED_TESTS;                                                  \

#define EMU_ADD(name)                                                          \
_EMU_FAILED_TESTS += _EMU_TEST_##name(                                         \
    emu_logging_enabled,                                                       \
    emu_color_enabled,                                                         \
    emu_indent+1                                                               \
)

#define EMU_DECLARE(name) int _EMU_TEST_##name(int, int, int)

#define EMU_RUN(name)                                                          \
_EMU_TEST_##name(                                                              \
    _EMU_SETTING_LOGGING_ENABLED,                                              \
    _EMU_SETTING_COLOR_ENABLED,                                                \
    0                                                                          \
)

#define EMU_PRINT_INDENT()                                                     \
do{                                                                            \
    for (int i = 0; i <= emu_indent; ++i)                                      \
    {                                                                          \
        printf(_EMU_LOG_STR_INDENT_BAR);                                       \
    }                                                                          \
}while(0)

#define EMU_PRINT_LINE_BREAK()                                                 \
do{EMU_PRINT_INDENT(); putchar('\n');}while(0)

#define EMU_DEFAULT_EPSILON (0.00001)

#define EMU_FAIL(...)                                                          \
do                                                                             \
{                                                                              \
    _EMU_TEST_RESULT = _EMU_TEST_FAILURE;                                      \
    _EMU_PRINT_FAILURE("EXPLICIT", printf(" " __VA_ARGS__ "\n"));              \
    goto _emu_label_end_test;                                                  \
}while(0)

// EXPECT TOOLS ////////////////////////////////////////////////////////////////
// EXPECT TRUE
#define EMU_EXPECT_TRUE(expr)                                                  \
_EMU_COND_TEMPLATE(                                                            \
    _EMU_EXPECT_TMPLT,                                                         \
    (expr),                                                                    \
    "EXPECT TRUE",                                                             \
    _EMU_LOG_GENERIC_FAILURE()                                                 \
)

// EXPECT FALSE
#define EMU_EXPECT_FALSE(expr)                                                 \
_EMU_COND_TEMPLATE(                                                            \
    _EMU_EXPECT_TMPLT,                                                         \
    !(expr),                                                                   \
    "EXPECT FALSE",                                                            \
    _EMU_LOG_GENERIC_FAILURE()                                                 \
)

// EXPECT EQ
#define EMU_EXPECT_EQ(a, b)                                                    \
_EMU_COND_TEMPLATE(                                                            \
    _EMU_EXPECT_TMPLT,                                                         \
    _EMU_IS_EQ(a,b),                                                           \
    "EXPECT EQ",                                                               \
    _EMU_LOG_GENERIC_FAILURE()                                                 \
)

#define EMU_EXPECT_EQ_CHAR(a, b)                                               \
_EMU_SET_CACHED_CHAR(a, b)                                                     \
_EMU_COND_TEMPLATE(                                                            \
    _EMU_EXPECT_TMPLT,                                                         \
    _EMU_IS_EQ(_EMU_CACHED_CHAR[0], _EMU_CACHED_CHAR[1]),                      \
    "EXPECT EQ CHAR",                                                          \
    _EMU_LOG_CHAR_FAILURE(                                                     \
        _EMU_CACHED_CHAR[0],                                                   \
        _EMU_CACHED_CHAR[1],                                                   \
        _EMU_LOG_STR_EQ                                                        \
    )                                                                          \
)

#define EMU_EXPECT_EQ_INT(a, b)                                                \
_EMU_SET_CACHED_INT(a, b)                                                      \
_EMU_COND_TEMPLATE(_EMU_EXPECT_TMPLT,                                          \
    _EMU_IS_EQ(_EMU_CACHED_INT[0], _EMU_CACHED_INT[1]),                        \
    "EXPECT EQ INT",                                                           \
    _EMU_LOG_INT_FAILURE(                                                      \
        _EMU_CACHED_INT[0],                                                    \
        _EMU_CACHED_INT[1],                                                    \
        _EMU_LOG_STR_EQ                                                        \
    )                                                                          \
)

#define EMU_EXPECT_EQ_UINT(a, b)                                               \
_EMU_SET_CACHED_UINT(a, b)                                                     \
_EMU_COND_TEMPLATE(_EMU_EXPECT_TMPLT,                                          \
    _EMU_IS_EQ(_EMU_CACHED_UINT[0], _EMU_CACHED_UINT[1]),                      \
    "EXPECT EQ UINT",                                                          \
    _EMU_LOG_UINT_FAILURE(                                                     \
        _EMU_CACHED_UINT[0],                                                   \
        _EMU_CACHED_UINT[1],                                                   \
        _EMU_LOG_STR_EQ                                                        \
    )                                                                          \
)

#define EMU_EXPECT_EQ_FLOAT(a, b)                                              \
_EMU_SET_CACHED_FLOAT(a, b)                                                    \
_EMU_COND_TEMPLATE(_EMU_EXPECT_TMPLT,                                          \
    _EMU_IS_EQ(_EMU_CACHED_FLOAT[0], _EMU_CACHED_FLOAT[1]),                    \
    "EXPECT EQ FLOAT",                                                         \
    _EMU_LOG_FLOAT_FAILURE(                                                    \
        _EMU_CACHED_FLOAT[0],                                                  \
        _EMU_CACHED_FLOAT[1],                                                  \
        _EMU_LOG_STR_EQ                                                        \
    )                                                                          \
)

// EXPECT NE
#define EMU_EXPECT_NE(a, b)                                                    \
_EMU_COND_TEMPLATE(                                                            \
    _EMU_EXPECT_TMPLT,                                                         \
    !_EMU_IS_EQ(a,b),                                                          \
    "EXPECT NE",                                                               \
    _EMU_LOG_GENERIC_FAILURE()                                                 \
)

#define EMU_EXPECT_NE_CHAR(a, b)                                               \
_EMU_SET_CACHED_CHAR(a, b)                                                     \
_EMU_COND_TEMPLATE(_EMU_EXPECT_TMPLT,                                          \
    !_EMU_IS_EQ(_EMU_CACHED_CHAR[0], _EMU_CACHED_CHAR[1]),                     \
    "EXPECT NE CHAR",                                                          \
    _EMU_LOG_CHAR_FAILURE(                                                     \
        _EMU_CACHED_CHAR[0],                                                   \
        _EMU_CACHED_CHAR[1],                                                   \
        _EMU_LOG_STR_NE                                                        \
    )                                                                          \
)

#define EMU_EXPECT_NE_INT(a, b)                                                \
_EMU_SET_CACHED_INT(a, b)                                                      \
_EMU_COND_TEMPLATE(_EMU_EXPECT_TMPLT,                                          \
    !_EMU_IS_EQ(_EMU_CACHED_INT[0], _EMU_CACHED_INT[1]),                       \
    "EXPECT NE INT",                                                           \
    _EMU_LOG_INT_FAILURE(                                                      \
        _EMU_CACHED_INT[0],                                                    \
        _EMU_CACHED_INT[1],                                                    \
        _EMU_LOG_STR_NE                                                        \
    )                                                                          \
)

#define EMU_EXPECT_NE_UINT(a, b)                                               \
_EMU_SET_CACHED_UINT(a, b)                                                     \
_EMU_COND_TEMPLATE(_EMU_EXPECT_TMPLT,                                          \
    !_EMU_IS_EQ(_EMU_CACHED_UINT[0], _EMU_CACHED_UINT[1]),                     \
    "EXPECT NE UINT",                                                          \
    _EMU_LOG_UINT_FAILURE(                                                     \
        _EMU_CACHED_UINT[0],                                                   \
        _EMU_CACHED_UINT[1],                                                   \
        _EMU_LOG_STR_NE                                                        \
    )                                                                          \
)

#define EMU_EXPECT_NE_FLOAT(a, b)                                              \
_EMU_SET_CACHED_FLOAT(a, b)                                                    \
_EMU_COND_TEMPLATE(_EMU_EXPECT_TMPLT,                                          \
    !_EMU_IS_EQ(_EMU_CACHED_FLOAT[0], _EMU_CACHED_FLOAT[1]),                   \
    "EXPECT NE FLOAT",                                                         \
    _EMU_LOG_FLOAT_FAILURE(                                                    \
        _EMU_CACHED_FLOAT[0],                                                  \
        _EMU_CACHED_FLOAT[1],                                                  \
        _EMU_LOG_STR_NE                                                        \
    )                                                                          \
)

// EXPECT GT
#define EMU_EXPECT_GT(a, b)                                                    \
_EMU_COND_TEMPLATE(                                                            \
    _EMU_EXPECT_TMPLT,                                                         \
    _EMU_IS_GT(a,b),                                                           \
    "EXPECT GT",                                                               \
    _EMU_LOG_GENERIC_FAILURE()                                                 \
)

#define EMU_EXPECT_GT_CHAR(a, b)                                               \
_EMU_SET_CACHED_CHAR(a, b)                                                     \
_EMU_COND_TEMPLATE(_EMU_EXPECT_TMPLT,                                          \
    _EMU_IS_GT(_EMU_CACHED_CHAR[0], _EMU_CACHED_CHAR[1]),                      \
    "EXPECT GT CHAR",                                                          \
    _EMU_LOG_CHAR_FAILURE(                                                     \
        _EMU_CACHED_CHAR[0],                                                   \
        _EMU_CACHED_CHAR[1],                                                   \
        _EMU_LOG_STR_GT                                                        \
    )                                                                          \
)

#define EMU_EXPECT_GT_INT(a, b)                                                \
_EMU_SET_CACHED_INT(a, b)                                                      \
_EMU_COND_TEMPLATE(_EMU_EXPECT_TMPLT,                                          \
    _EMU_IS_GT(_EMU_CACHED_INT[0], _EMU_CACHED_INT[1]),                        \
    "EXPECT GT INT",                                                           \
    _EMU_LOG_INT_FAILURE(                                                      \
        _EMU_CACHED_INT[0],                                                    \
        _EMU_CACHED_INT[1],                                                    \
        _EMU_LOG_STR_GT                                                        \
    )                                                                          \
)

#define EMU_EXPECT_GT_UINT(a, b)                                               \
_EMU_SET_CACHED_UINT(a, b)                                                     \
_EMU_COND_TEMPLATE(_EMU_EXPECT_TMPLT,                                          \
    _EMU_IS_GT(_EMU_CACHED_UINT[0], _EMU_CACHED_UINT[1]),                      \
    "EXPECT GT UINT",                                                          \
    _EMU_LOG_UINT_FAILURE(                                                     \
        _EMU_CACHED_UINT[0],                                                   \
        _EMU_CACHED_UINT[1],                                                   \
        _EMU_LOG_STR_GT                                                        \
    )                                                                          \
)

#define EMU_EXPECT_GT_FLOAT(a, b)                                              \
_EMU_SET_CACHED_FLOAT(a, b)                                                    \
_EMU_COND_TEMPLATE(_EMU_EXPECT_TMPLT,                                          \
    _EMU_IS_GT(_EMU_CACHED_FLOAT[0], _EMU_CACHED_FLOAT[1]),                    \
    "EXPECT GT FLOAT",                                                         \
    _EMU_LOG_FLOAT_FAILURE(                                                    \
        _EMU_CACHED_FLOAT[0],                                                  \
        _EMU_CACHED_FLOAT[1],                                                  \
        _EMU_LOG_STR_GT                                                        \
    )                                                                          \
)

// EXPECT GE
#define EMU_EXPECT_GE(a, b)                                                    \
_EMU_COND_TEMPLATE(                                                            \
    _EMU_EXPECT_TMPLT,                                                         \
    _EMU_IS_GE(a,b),                                                           \
    "EXPECT GE",                                                               \
    _EMU_LOG_GENERIC_FAILURE()                                                 \
)

#define EMU_EXPECT_GE_CHAR(a, b)                                               \
_EMU_SET_CACHED_CHAR(a, b)                                                     \
_EMU_COND_TEMPLATE(_EMU_EXPECT_TMPLT,                                          \
    _EMU_IS_GE(_EMU_CACHED_CHAR[0], _EMU_CACHED_CHAR[1]),                      \
    "EXPECT GE CHAR",                                                          \
    _EMU_LOG_CHAR_FAILURE(                                                     \
        _EMU_CACHED_CHAR[0],                                                   \
        _EMU_CACHED_CHAR[1],                                                   \
        _EMU_LOG_STR_GE                                                        \
    )                                                                          \
)

#define EMU_EXPECT_GE_INT(a, b)                                                \
_EMU_SET_CACHED_INT(a, b)                                                      \
_EMU_COND_TEMPLATE(_EMU_EXPECT_TMPLT,                                          \
    _EMU_IS_GE(_EMU_CACHED_INT[0], _EMU_CACHED_INT[1]),                        \
    "EXPECT GE INT",                                                           \
    _EMU_LOG_INT_FAILURE(                                                      \
        _EMU_CACHED_INT[0],                                                    \
        _EMU_CACHED_INT[1],                                                    \
        _EMU_LOG_STR_GE)                                                       \
)

#define EMU_EXPECT_GE_UINT(a, b)                                               \
_EMU_SET_CACHED_UINT(a, b)                                                     \
_EMU_COND_TEMPLATE(_EMU_EXPECT_TMPLT,                                          \
    _EMU_IS_GE(_EMU_CACHED_UINT[0], _EMU_CACHED_UINT[1]),                      \
    "EXPECT GE UINT",                                                          \
    _EMU_LOG_UINT_FAILURE(                                                     \
        _EMU_CACHED_UINT[0],                                                   \
        _EMU_CACHED_UINT[1],                                                   \
        _EMU_LOG_STR_GE                                                        \
    )                                                                          \
)

#define EMU_EXPECT_GE_FLOAT(a, b)                                              \
_EMU_SET_CACHED_FLOAT(a, b)                                                    \
_EMU_COND_TEMPLATE(_EMU_EXPECT_TMPLT,                                          \
    _EMU_IS_GE(_EMU_CACHED_FLOAT[0], _EMU_CACHED_FLOAT[1]),                    \
    "EXPECT GE FLOAT",                                                         \
    _EMU_LOG_FLOAT_FAILURE(                                                    \
        _EMU_CACHED_FLOAT[0],                                                  \
        _EMU_CACHED_FLOAT[1],                                                  \
        _EMU_LOG_STR_GE                                                        \
    )                                                                          \
)

// EXPECT LT
#define EMU_EXPECT_LT(a, b)                                                    \
_EMU_COND_TEMPLATE(                                                            \
    _EMU_EXPECT_TMPLT,                                                         \
    _EMU_IS_LT(a,b),                                                           \
    "EXPECT LT",                                                               \
    _EMU_LOG_GENERIC_FAILURE()                                                 \
)

#define EMU_EXPECT_LT_CHAR(a, b)                                               \
_EMU_SET_CACHED_CHAR(a, b)                                                     \
_EMU_COND_TEMPLATE(_EMU_EXPECT_TMPLT,                                          \
    _EMU_IS_LT(_EMU_CACHED_CHAR[0], _EMU_CACHED_CHAR[1]),                      \
    "EXPECT LT CHAR",                                                          \
    _EMU_LOG_CHAR_FAILURE(                                                     \
        _EMU_CACHED_CHAR[0],                                                   \
        _EMU_CACHED_CHAR[1],                                                   \
        _EMU_LOG_STR_LT                                                        \
    )                                                                          \
)

#define EMU_EXPECT_LT_INT(a, b)                                                \
_EMU_SET_CACHED_INT(a, b)                                                      \
_EMU_COND_TEMPLATE(_EMU_EXPECT_TMPLT,                                          \
    _EMU_IS_LT(_EMU_CACHED_INT[0], _EMU_CACHED_INT[1]),                        \
    "EXPECT LT INT",                                                           \
    _EMU_LOG_INT_FAILURE(                                                      \
        _EMU_CACHED_INT[0],                                                    \
        _EMU_CACHED_INT[1],                                                    \
        _EMU_LOG_STR_LT                                                        \
    )                                                                          \
)

#define EMU_EXPECT_LT_UINT(a, b)                                               \
_EMU_SET_CACHED_UINT(a, b)                                                     \
_EMU_COND_TEMPLATE(_EMU_EXPECT_TMPLT,                                          \
    _EMU_IS_LT(_EMU_CACHED_UINT[0], _EMU_CACHED_UINT[1]),                      \
    "EXPECT LT UINT",                                                          \
    _EMU_LOG_UINT_FAILURE(                                                     \
        _EMU_CACHED_UINT[0],                                                   \
        _EMU_CACHED_UINT[1],                                                   \
        _EMU_LOG_STR_LT                                                        \
    )                                                                          \
)

#define EMU_EXPECT_LT_FLOAT(a, b)                                              \
_EMU_SET_CACHED_FLOAT(a, b)                                                    \
_EMU_COND_TEMPLATE(_EMU_EXPECT_TMPLT,                                          \
    _EMU_IS_LT(_EMU_CACHED_FLOAT[0], _EMU_CACHED_FLOAT[1]),                    \
    "EXPECT LT FLOAT",                                                         \
    _EMU_LOG_FLOAT_FAILURE(                                                    \
        _EMU_CACHED_FLOAT[0],                                                  \
        _EMU_CACHED_FLOAT[1],                                                  \
        _EMU_LOG_STR_LT                                                        \
    )                                                                          \
)

// EXPECT LE
#define EMU_EXPECT_LE(a, b)                                                    \
_EMU_COND_TEMPLATE(                                                            \
    _EMU_EXPECT_TMPLT,                                                         \
    _EMU_IS_LE(a,b),                                                           \
    "EXPECT LE",                                                               \
    _EMU_LOG_GENERIC_FAILURE()                                                 \
)

#define EMU_EXPECT_LE_CHAR(a, b)                                               \
_EMU_SET_CACHED_CHAR(a, b)                                                     \
_EMU_COND_TEMPLATE(_EMU_EXPECT_TMPLT,                                          \
    _EMU_IS_LE(_EMU_CACHED_CHAR[0], _EMU_CACHED_CHAR[1]),                      \
    "EXPECT LE CHAR",                                                          \
    _EMU_LOG_CHAR_FAILURE(                                                     \
        _EMU_CACHED_CHAR[0],                                                   \
        _EMU_CACHED_CHAR[1],                                                   \
        _EMU_LOG_STR_LE                                                        \
    )                                                                          \
)

#define EMU_EXPECT_LE_INT(a, b)                                                \
_EMU_SET_CACHED_INT(a, b)                                                      \
_EMU_COND_TEMPLATE(_EMU_EXPECT_TMPLT,                                          \
    _EMU_IS_LE(_EMU_CACHED_INT[0], _EMU_CACHED_INT[1]),                        \
    "EXPECT LE INT",                                                           \
    _EMU_LOG_INT_FAILURE(                                                      \
        _EMU_CACHED_INT[0],                                                    \
        _EMU_CACHED_INT[1],                                                    \
        _EMU_LOG_STR_LE                                                        \
    )                                                                          \
)

#define EMU_EXPECT_LE_UINT(a, b)                                               \
_EMU_SET_CACHED_UINT(a, b)                                                     \
_EMU_COND_TEMPLATE(_EMU_EXPECT_TMPLT,                                          \
    _EMU_IS_LE(_EMU_CACHED_UINT[0], _EMU_CACHED_UINT[1]),                      \
    "EXPECT LE UINT",                                                          \
    _EMU_LOG_UINT_FAILURE(                                                     \
        _EMU_CACHED_UINT[0],                                                   \
        _EMU_CACHED_UINT[1],                                                   \
        _EMU_LOG_STR_LE                                                        \
    )                                                                          \
)

#define EMU_EXPECT_LE_FLOAT(a, b)                                              \
_EMU_SET_CACHED_FLOAT(a, b)                                                    \
_EMU_COND_TEMPLATE(_EMU_EXPECT_TMPLT,                                          \
    _EMU_IS_LE(_EMU_CACHED_FLOAT[0], _EMU_CACHED_FLOAT[1]),                    \
    "EXPECT LE FLOAT",                                                         \
    _EMU_LOG_FLOAT_FAILURE(                                                    \
        _EMU_CACHED_FLOAT[0],                                                  \
        _EMU_CACHED_FLOAT[1],                                                  \
        _EMU_LOG_STR_LE                                                        \
    )                                                                          \
)

// EXPECT NULL
#define EMU_EXPECT_NULL(expr)                                                  \
_EMU_COND_TEMPLATE(                                                            \
    _EMU_EXPECT_TMPLT,                                                         \
    _EMU_IS_NULL(expr),                                                        \
    "EXPECT NULL",                                                             \
    _EMU_LOG_GENERIC_FAILURE()                                                 \
)

// EXPECT NOT NULL
#define EMU_EXPECT_NOT_NULL(expr)                                              \
_EMU_COND_TEMPLATE(                                                            \
    _EMU_EXPECT_TMPLT,                                                         \
    !_EMU_IS_NULL(expr),                                                       \
    "EXPECT NOT NULL",                                                         \
    _EMU_LOG_GENERIC_FAILURE()                                                 \
)                                                                              \

// EXPECT FEQ
#define EMU_EXPECT_FEQ(a, b, epsilon)                                          \
_EMU_SET_CACHED_FLOAT(a, b)                                                    \
_EMU_COND_TEMPLATE(_EMU_EXPECT_TMPLT,                                          \
    _EMU_IS_FEQ(_EMU_CACHED_FLOAT[0], _EMU_CACHED_FLOAT[1], epsilon),          \
    "EXPECT FEQ",                                                              \
    _EMU_LOG_FLOAT_FAILURE(_EMU_CACHED_FLOAT[0], _EMU_CACHED_FLOAT[1],         \
        _EMU_LOG_STR_EQ)                                                       \
)

// EXPECT STREQ
#define EMU_EXPECT_STREQ(a, b)                                                 \
_EMU_COND_TEMPLATE(_EMU_EXPECT_TMPLT,                                          \
    (strcmp(a, b) == 0),                                                       \
    "EXPECT STREQ",                                                            \
    _EMU_LOG_GENERIC_FAILURE()                                                 \
)

// EXPECT STRNE
#define EMU_EXPECT_STRNE(a, b)                                                 \
_EMU_COND_TEMPLATE(_EMU_EXPECT_TMPLT,                                          \
    (strcmp(a, b) != 0),                                                       \
    "EXPECT STRNE",                                                            \
    _EMU_LOG_GENERIC_FAILURE()                                                 \
)

#ifdef __cplusplus
// EXPECT THROW
#define EMU_EXPECT_THROW(expr)                                                 \
_EMU_THROW_TEMPLATE(                                                           \
    _EMU_EXPECT_TMPLT,                                                         \
    expr,                                                                      \
    "EXPECT THROW"                                                             \
)

// EXPECT THROW TYPE
#define EMU_EXPECT_THROW_TYPE(expr, excep_t)                                   \
_EMU_THROW_TYPE_TEMPLATE(                                                      \
    _EMU_EXPECT_TMPLT,                                                         \
    expr,                                                                      \
    excep_t,                                                                   \
    "EXPECT THROW TYPE",                                                       \
    _EMU_LOG_EXCEPTION_FAILURE(excep_t)                                        \
)

// EXPECT NO THROW
#define EMU_EXPECT_NO_THROW(expr)                                              \
_EMU_NO_THROW_TEMPLATE(                                                        \
    _EMU_EXPECT_TMPLT,                                                         \
    expr,                                                                      \
    "EXPECT NO THROW"                                                          \
)
#endif // !__cplusplus

// ASSERT TOOLS ////////////////////////////////////////////////////////////////
// ASSERT TRUE
#define EMU_ASSERT_TRUE(expr)                                                  \
_EMU_COND_TEMPLATE(                                                            \
    _EMU_ASSERT_TMPLT,                                                         \
    (expr),                                                                    \
    "ASSERT TRUE",                                                             \
    _EMU_LOG_GENERIC_FAILURE()                                                 \
)

// ASSERT FALSE
#define EMU_ASSERT_FALSE(expr)                                                 \
_EMU_COND_TEMPLATE(                                                            \
    _EMU_ASSERT_TMPLT,                                                         \
    !(expr),                                                                   \
    "ASSERT FALSE",                                                            \
    _EMU_LOG_GENERIC_FAILURE()                                                 \
)

// ASSERT EQ
#define EMU_ASSERT_EQ(a, b)                                                    \
_EMU_COND_TEMPLATE(                                                            \
    _EMU_ASSERT_TMPLT,                                                         \
    _EMU_IS_EQ(a,b),                                                           \
    "ASSERT EQ",                                                               \
    _EMU_LOG_GENERIC_FAILURE()                                                 \
)

#define EMU_ASSERT_EQ_CHAR(a, b)                                               \
_EMU_SET_CACHED_CHAR(a, b)                                                     \
_EMU_COND_TEMPLATE(                                                            \
    _EMU_ASSERT_TMPLT,                                                         \
    _EMU_IS_EQ(_EMU_CACHED_CHAR[0], _EMU_CACHED_CHAR[1]),                      \
    "ASSERT EQ CHAR",                                                          \
    _EMU_LOG_CHAR_FAILURE(                                                     \
        _EMU_CACHED_CHAR[0],                                                   \
        _EMU_CACHED_CHAR[1],                                                   \
        _EMU_LOG_STR_EQ                                                        \
    )                                                                          \
)

#define EMU_ASSERT_EQ_INT(a, b)                                                \
_EMU_SET_CACHED_INT(a, b)                                                      \
_EMU_COND_TEMPLATE(_EMU_ASSERT_TMPLT,                                          \
    _EMU_IS_EQ(_EMU_CACHED_INT[0], _EMU_CACHED_INT[1]),                        \
    "ASSERT EQ INT",                                                           \
    _EMU_LOG_INT_FAILURE(                                                      \
        _EMU_CACHED_INT[0],                                                    \
        _EMU_CACHED_INT[1],                                                    \
        _EMU_LOG_STR_EQ                                                        \
    )                                                                          \
)

#define EMU_ASSERT_EQ_UINT(a, b)                                               \
_EMU_SET_CACHED_UINT(a, b)                                                     \
_EMU_COND_TEMPLATE(_EMU_ASSERT_TMPLT,                                          \
    _EMU_IS_EQ(_EMU_CACHED_UINT[0], _EMU_CACHED_UINT[1]),                      \
    "ASSERT EQ UINT",                                                          \
    _EMU_LOG_UINT_FAILURE(                                                     \
        _EMU_CACHED_UINT[0],                                                   \
        _EMU_CACHED_UINT[1],                                                   \
        _EMU_LOG_STR_EQ                                                        \
    )                                                                          \
)

#define EMU_ASSERT_EQ_FLOAT(a, b)                                              \
_EMU_SET_CACHED_FLOAT(a, b)                                                    \
_EMU_COND_TEMPLATE(_EMU_ASSERT_TMPLT,                                          \
    _EMU_IS_EQ(_EMU_CACHED_FLOAT[0], _EMU_CACHED_FLOAT[1]),                    \
    "ASSERT EQ FLOAT",                                                         \
    _EMU_LOG_FLOAT_FAILURE(                                                    \
        _EMU_CACHED_FLOAT[0],                                                  \
        _EMU_CACHED_FLOAT[1],                                                  \
        _EMU_LOG_STR_EQ                                                        \
    )                                                                          \
)

// ASSERT NE
#define EMU_ASSERT_NE(a, b)                                                    \
_EMU_COND_TEMPLATE(                                                            \
    _EMU_ASSERT_TMPLT,                                                         \
    !_EMU_IS_EQ(a,b),                                                          \
    "ASSERT NE",                                                               \
    _EMU_LOG_GENERIC_FAILURE()                                                 \
)

#define EMU_ASSERT_NE_CHAR(a, b)                                               \
_EMU_SET_CACHED_CHAR(a, b)                                                     \
_EMU_COND_TEMPLATE(_EMU_ASSERT_TMPLT,                                          \
    !_EMU_IS_EQ(_EMU_CACHED_CHAR[0], _EMU_CACHED_CHAR[1]),                     \
    "ASSERT NE CHAR",                                                          \
    _EMU_LOG_CHAR_FAILURE(                                                     \
        _EMU_CACHED_CHAR[0],                                                   \
        _EMU_CACHED_CHAR[1],                                                   \
        _EMU_LOG_STR_NE                                                        \
    )                                                                          \
)

#define EMU_ASSERT_NE_INT(a, b)                                                \
_EMU_SET_CACHED_INT(a, b)                                                      \
_EMU_COND_TEMPLATE(_EMU_ASSERT_TMPLT,                                          \
    !_EMU_IS_EQ(_EMU_CACHED_INT[0], _EMU_CACHED_INT[1]),                       \
    "ASSERT NE INT",                                                           \
    _EMU_LOG_INT_FAILURE(                                                      \
        _EMU_CACHED_INT[0],                                                    \
        _EMU_CACHED_INT[1],                                                    \
        _EMU_LOG_STR_NE                                                        \
    )                                                                          \
)

#define EMU_ASSERT_NE_UINT(a, b)                                               \
_EMU_SET_CACHED_UINT(a, b)                                                     \
_EMU_COND_TEMPLATE(_EMU_ASSERT_TMPLT,                                          \
    !_EMU_IS_EQ(_EMU_CACHED_UINT[0], _EMU_CACHED_UINT[1]),                     \
    "ASSERT NE UINT",                                                          \
    _EMU_LOG_UINT_FAILURE(                                                     \
        _EMU_CACHED_UINT[0],                                                   \
        _EMU_CACHED_UINT[1],                                                   \
        _EMU_LOG_STR_NE                                                        \
    )                                                                          \
)

#define EMU_ASSERT_NE_FLOAT(a, b)                                              \
_EMU_SET_CACHED_FLOAT(a, b)                                                    \
_EMU_COND_TEMPLATE(_EMU_ASSERT_TMPLT,                                          \
    !_EMU_IS_EQ(_EMU_CACHED_FLOAT[0], _EMU_CACHED_FLOAT[1]),                   \
    "ASSERT NE FLOAT",                                                         \
    _EMU_LOG_FLOAT_FAILURE(                                                    \
        _EMU_CACHED_FLOAT[0],                                                  \
        _EMU_CACHED_FLOAT[1],                                                  \
        _EMU_LOG_STR_NE                                                        \
    )                                                                          \
)

// ASSERT GT
#define EMU_ASSERT_GT(a, b)                                                    \
_EMU_COND_TEMPLATE(                                                            \
    _EMU_ASSERT_TMPLT,                                                         \
    _EMU_IS_GT(a,b),                                                           \
    "ASSERT GT",                                                               \
    _EMU_LOG_GENERIC_FAILURE()                                                 \
)

#define EMU_ASSERT_GT_CHAR(a, b)                                               \
_EMU_SET_CACHED_CHAR(a, b)                                                     \
_EMU_COND_TEMPLATE(_EMU_ASSERT_TMPLT,                                          \
    _EMU_IS_GT(_EMU_CACHED_CHAR[0], _EMU_CACHED_CHAR[1]),                      \
    "ASSERT GT CHAR",                                                          \
    _EMU_LOG_CHAR_FAILURE(                                                     \
        _EMU_CACHED_CHAR[0],                                                   \
        _EMU_CACHED_CHAR[1],                                                   \
        _EMU_LOG_STR_GT                                                        \
    )                                                                          \
)

#define EMU_ASSERT_GT_INT(a, b)                                                \
_EMU_SET_CACHED_INT(a, b)                                                      \
_EMU_COND_TEMPLATE(_EMU_ASSERT_TMPLT,                                          \
    _EMU_IS_GT(_EMU_CACHED_INT[0], _EMU_CACHED_INT[1]),                        \
    "ASSERT GT INT",                                                           \
    _EMU_LOG_INT_FAILURE(                                                      \
        _EMU_CACHED_INT[0],                                                    \
        _EMU_CACHED_INT[1],                                                    \
        _EMU_LOG_STR_GT                                                        \
    )                                                                          \
)

#define EMU_ASSERT_GT_UINT(a, b)                                               \
_EMU_SET_CACHED_UINT(a, b)                                                     \
_EMU_COND_TEMPLATE(_EMU_ASSERT_TMPLT,                                          \
    _EMU_IS_GT(_EMU_CACHED_UINT[0], _EMU_CACHED_UINT[1]),                      \
    "ASSERT GT UINT",                                                          \
    _EMU_LOG_UINT_FAILURE(                                                     \
        _EMU_CACHED_UINT[0],                                                   \
        _EMU_CACHED_UINT[1],                                                   \
        _EMU_LOG_STR_GT                                                        \
    )                                                                          \
)

#define EMU_ASSERT_GT_FLOAT(a, b)                                              \
_EMU_SET_CACHED_FLOAT(a, b)                                                    \
_EMU_COND_TEMPLATE(_EMU_ASSERT_TMPLT,                                          \
    _EMU_IS_GT(_EMU_CACHED_FLOAT[0], _EMU_CACHED_FLOAT[1]),                    \
    "ASSERT GT FLOAT",                                                         \
    _EMU_LOG_FLOAT_FAILURE(                                                    \
        _EMU_CACHED_FLOAT[0],                                                  \
        _EMU_CACHED_FLOAT[1],                                                  \
        _EMU_LOG_STR_GT                                                        \
    )                                                                          \
)

// ASSERT GE
#define EMU_ASSERT_GE(a, b)                                                    \
_EMU_COND_TEMPLATE(                                                            \
    _EMU_ASSERT_TMPLT,                                                         \
    _EMU_IS_GE(a,b),                                                           \
    "ASSERT GE",                                                               \
    _EMU_LOG_GENERIC_FAILURE()                                                 \
)

#define EMU_ASSERT_GE_CHAR(a, b)                                               \
_EMU_SET_CACHED_CHAR(a, b)                                                     \
_EMU_COND_TEMPLATE(_EMU_ASSERT_TMPLT,                                          \
    _EMU_IS_GE(_EMU_CACHED_CHAR[0], _EMU_CACHED_CHAR[1]),                      \
    "ASSERT GE CHAR",                                                          \
    _EMU_LOG_CHAR_FAILURE(                                                     \
        _EMU_CACHED_CHAR[0],                                                   \
        _EMU_CACHED_CHAR[1],                                                   \
        _EMU_LOG_STR_GE                                                        \
    )                                                                          \
)

#define EMU_ASSERT_GE_INT(a, b)                                                \
_EMU_SET_CACHED_INT(a, b)                                                      \
_EMU_COND_TEMPLATE(_EMU_ASSERT_TMPLT,                                          \
    _EMU_IS_GE(_EMU_CACHED_INT[0], _EMU_CACHED_INT[1]),                        \
    "ASSERT GE INT",                                                           \
    _EMU_LOG_INT_FAILURE(                                                      \
        _EMU_CACHED_INT[0],                                                    \
        _EMU_CACHED_INT[1],                                                    \
        _EMU_LOG_STR_GE)                                                       \
)

#define EMU_ASSERT_GE_UINT(a, b)                                               \
_EMU_SET_CACHED_UINT(a, b)                                                     \
_EMU_COND_TEMPLATE(_EMU_ASSERT_TMPLT,                                          \
    _EMU_IS_GE(_EMU_CACHED_UINT[0], _EMU_CACHED_UINT[1]),                      \
    "ASSERT GE UINT",                                                          \
    _EMU_LOG_UINT_FAILURE(                                                     \
        _EMU_CACHED_UINT[0],                                                   \
        _EMU_CACHED_UINT[1],                                                   \
        _EMU_LOG_STR_GE                                                        \
    )                                                                          \
)

#define EMU_ASSERT_GE_FLOAT(a, b)                                              \
_EMU_SET_CACHED_FLOAT(a, b)                                                    \
_EMU_COND_TEMPLATE(_EMU_ASSERT_TMPLT,                                          \
    _EMU_IS_GE(_EMU_CACHED_FLOAT[0], _EMU_CACHED_FLOAT[1]),                    \
    "ASSERT GE FLOAT",                                                         \
    _EMU_LOG_FLOAT_FAILURE(                                                    \
        _EMU_CACHED_FLOAT[0],                                                  \
        _EMU_CACHED_FLOAT[1],                                                  \
        _EMU_LOG_STR_GE                                                        \
    )                                                                          \
)

// ASSERT LT
#define EMU_ASSERT_LT(a, b)                                                    \
_EMU_COND_TEMPLATE(                                                            \
    _EMU_ASSERT_TMPLT,                                                         \
    _EMU_IS_LT(a,b),                                                           \
    "ASSERT LT",                                                               \
    _EMU_LOG_GENERIC_FAILURE()                                                 \
)

#define EMU_ASSERT_LT_CHAR(a, b)                                               \
_EMU_SET_CACHED_CHAR(a, b)                                                     \
_EMU_COND_TEMPLATE(_EMU_ASSERT_TMPLT,                                          \
    _EMU_IS_LT(_EMU_CACHED_CHAR[0], _EMU_CACHED_CHAR[1]),                      \
    "ASSERT LT CHAR",                                                          \
    _EMU_LOG_CHAR_FAILURE(                                                     \
        _EMU_CACHED_CHAR[0],                                                   \
        _EMU_CACHED_CHAR[1],                                                   \
        _EMU_LOG_STR_LT                                                        \
    )                                                                          \
)

#define EMU_ASSERT_LT_INT(a, b)                                                \
_EMU_SET_CACHED_INT(a, b)                                                      \
_EMU_COND_TEMPLATE(_EMU_ASSERT_TMPLT,                                          \
    _EMU_IS_LT(_EMU_CACHED_INT[0], _EMU_CACHED_INT[1]),                        \
    "ASSERT LT INT",                                                           \
    _EMU_LOG_INT_FAILURE(                                                      \
        _EMU_CACHED_INT[0],                                                    \
        _EMU_CACHED_INT[1],                                                    \
        _EMU_LOG_STR_LT                                                        \
    )                                                                          \
)

#define EMU_ASSERT_LT_UINT(a, b)                                               \
_EMU_SET_CACHED_UINT(a, b)                                                     \
_EMU_COND_TEMPLATE(_EMU_ASSERT_TMPLT,                                          \
    _EMU_IS_LT(_EMU_CACHED_UINT[0], _EMU_CACHED_UINT[1]),                      \
    "ASSERT LT UINT",                                                          \
    _EMU_LOG_UINT_FAILURE(                                                     \
        _EMU_CACHED_UINT[0],                                                   \
        _EMU_CACHED_UINT[1],                                                   \
        _EMU_LOG_STR_LT                                                        \
    )                                                                          \
)

#define EMU_ASSERT_LT_FLOAT(a, b)                                              \
_EMU_SET_CACHED_FLOAT(a, b)                                                    \
_EMU_COND_TEMPLATE(_EMU_ASSERT_TMPLT,                                          \
    _EMU_IS_LT(_EMU_CACHED_FLOAT[0], _EMU_CACHED_FLOAT[1]),                    \
    "ASSERT LT FLOAT",                                                         \
    _EMU_LOG_FLOAT_FAILURE(                                                    \
        _EMU_CACHED_FLOAT[0],                                                  \
        _EMU_CACHED_FLOAT[1],                                                  \
        _EMU_LOG_STR_LT                                                        \
    )                                                                          \
)

// ASSERT LE
#define EMU_ASSERT_LE(a, b)                                                    \
_EMU_COND_TEMPLATE(                                                            \
    _EMU_ASSERT_TMPLT,                                                         \
    _EMU_IS_LE(a,b),                                                           \
    "ASSERT LE",                                                               \
    _EMU_LOG_GENERIC_FAILURE()                                                 \
)

#define EMU_ASSERT_LE_CHAR(a, b)                                               \
_EMU_SET_CACHED_CHAR(a, b)                                                     \
_EMU_COND_TEMPLATE(_EMU_ASSERT_TMPLT,                                          \
    _EMU_IS_LE(_EMU_CACHED_CHAR[0], _EMU_CACHED_CHAR[1]),                      \
    "ASSERT LE CHAR",                                                          \
    _EMU_LOG_CHAR_FAILURE(                                                     \
        _EMU_CACHED_CHAR[0],                                                   \
        _EMU_CACHED_CHAR[1],                                                   \
        _EMU_LOG_STR_LE                                                        \
    )                                                                          \
)

#define EMU_ASSERT_LE_INT(a, b)                                                \
_EMU_SET_CACHED_INT(a, b)                                                      \
_EMU_COND_TEMPLATE(_EMU_ASSERT_TMPLT,                                          \
    _EMU_IS_LE(_EMU_CACHED_INT[0], _EMU_CACHED_INT[1]),                        \
    "ASSERT LE INT",                                                           \
    _EMU_LOG_INT_FAILURE(                                                      \
        _EMU_CACHED_INT[0],                                                    \
        _EMU_CACHED_INT[1],                                                    \
        _EMU_LOG_STR_LE                                                        \
    )                                                                          \
)

#define EMU_ASSERT_LE_UINT(a, b)                                               \
_EMU_SET_CACHED_UINT(a, b)                                                     \
_EMU_COND_TEMPLATE(_EMU_ASSERT_TMPLT,                                          \
    _EMU_IS_LE(_EMU_CACHED_UINT[0], _EMU_CACHED_UINT[1]),                      \
    "ASSERT LE UINT",                                                          \
    _EMU_LOG_UINT_FAILURE(                                                     \
        _EMU_CACHED_UINT[0],                                                   \
        _EMU_CACHED_UINT[1],                                                   \
        _EMU_LOG_STR_LE                                                        \
    )                                                                          \
)

#define EMU_ASSERT_LE_FLOAT(a, b)                                              \
_EMU_SET_CACHED_FLOAT(a, b)                                                    \
_EMU_COND_TEMPLATE(_EMU_ASSERT_TMPLT,                                          \
    _EMU_IS_LE(_EMU_CACHED_FLOAT[0], _EMU_CACHED_FLOAT[1]),                    \
    "ASSERT LE FLOAT",                                                         \
    _EMU_LOG_FLOAT_FAILURE(                                                    \
        _EMU_CACHED_FLOAT[0],                                                  \
        _EMU_CACHED_FLOAT[1],                                                  \
        _EMU_LOG_STR_LE                                                        \
    )                                                                          \
)

// ASSERT NULL
#define EMU_ASSERT_NULL(expr)                                                  \
_EMU_COND_TEMPLATE(                                                            \
    _EMU_ASSERT_TMPLT,                                                         \
    _EMU_IS_NULL(expr),                                                        \
    "ASSERT NULL",                                                             \
    _EMU_LOG_GENERIC_FAILURE()                                                 \
)

// ASSERT NOT NULL
#define EMU_ASSERT_NOT_NULL(expr)                                              \
_EMU_COND_TEMPLATE(                                                            \
    _EMU_ASSERT_TMPLT,                                                         \
    !_EMU_IS_NULL(expr),                                                       \
    "ASSERT NOT NULL",                                                         \
    _EMU_LOG_GENERIC_FAILURE()                                                 \
)                                                                              \

// ASSERT FEQ
#define EMU_ASSERT_FEQ(a, b, epsilon)                                          \
_EMU_SET_CACHED_FLOAT(a, b)                                                    \
_EMU_COND_TEMPLATE(_EMU_ASSERT_TMPLT,                                          \
    _EMU_IS_FEQ(_EMU_CACHED_FLOAT[0], _EMU_CACHED_FLOAT[1], epsilon),          \
    "ASSERT FEQ",                                                              \
    _EMU_LOG_FLOAT_FAILURE(_EMU_CACHED_FLOAT[0], _EMU_CACHED_FLOAT[1],         \
        _EMU_LOG_STR_EQ)                                                       \
)

// ASSERT STREQ
#define EMU_ASSERT_STREQ(a, b)                                                 \
_EMU_COND_TEMPLATE(_EMU_ASSERT_TMPLT,                                          \
    (strcmp(a, b) == 0),                                                       \
    "ASSERT STREQ",                                                            \
    _EMU_LOG_GENERIC_FAILURE()                                                 \
)

// ASSERT STRNE
#define EMU_ASSERT_STRNE(a, b)                                                 \
_EMU_COND_TEMPLATE(_EMU_ASSERT_TMPLT,                                          \
    (strcmp(a, b) != 0),                                                       \
    "ASSERT STRNE",                                                            \
    _EMU_LOG_GENERIC_FAILURE()                                                 \
)

#ifdef __cplusplus
// ASSERT THROW
#define EMU_ASSERT_THROW(expr)                                                 \
_EMU_THROW_TEMPLATE(                                                           \
    _EMU_ASSERT_TMPLT,                                                         \
    expr,                                                                      \
    "ASSERT THROW"                                                             \
)

// ASSERT THROW TYPE
#define EMU_ASSERT_THROW_TYPE(expr, excep_t)                                   \
_EMU_THROW_TYPE_TEMPLATE(                                                      \
    _EMU_ASSERT_TMPLT,                                                         \
    expr,                                                                      \
    excep_t,                                                                   \
    "ASSERT THROW TYPE",                                                       \
    _EMU_LOG_EXCEPTION_FAILURE(excep_t)                                        \
)

// ASSERT NO THROW
#define EMU_ASSERT_NO_THROW(expr)                                              \
_EMU_NO_THROW_TEMPLATE(                                                        \
    _EMU_ASSERT_TMPLT,                                                         \
    expr,                                                                      \
    "ASSERT NO THROW"                                                          \
)
#endif // !__cplusplus

#endif // !_EMUTEST_H_