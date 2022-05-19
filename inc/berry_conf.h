#ifndef BERRY_CONF_H
#define BERRY_CONF_H

#include <assert.h>

/* Macro: BE_DEBUG
 * Berry interpreter debug switch.
 * default: 0
 **/
#ifndef BE_DEBUG
#define BE_DEBUG                        0
#endif

/* Macro: BE_SINGLE_FLOAT
 * Select floating point precision.
 * Use double-precision floating-point numbers when the value
 * is 0 (default), otherwise use single-precision floating-point
 * numbers.
 * default: 0
 **/
#define BE_SINGLE_FLOAT                 0

/* Macro: BE_LONGLONG_INT
 * Select integer length.
 * If the value is 0, use an integer of type int, use a long
 * integer type when the value is 1, and use a long long integer
 * type when the value is 2.
 * default: 2
 */
#define BE_INTGER_TYPE                  2

/* Macro: BE_USE_PRECOMPILED_OBJECT
 * Use precompiled objects to avoid creating these objects at
 * runtime. Enable this macro can greatly optimize RAM usage.
 * default: 1
 **/
#define BE_USE_PRECOMPILED_OBJECT       1

/* Macro: BE_DEBUG_RUNTIME_INFO
 * Set runtime error debugging information.
 * 0: unable to output source file and line number at runtime.
 * 1: output source file and line number information at runtime.
 * 2: the information use uint16_t type (save space)
 * default: 1
 **/
#define BE_DEBUG_RUNTIME_INFO           1

/* Macro: BE_DEBUG_DUMP_LEVEL
 * Set debugging code-dump information.
 * 0: disable code-dump.
 * 1: enable the function be_dumpclosure.
 * 2: enable be_debug_ins_info on the basis of case 1.
 * default: 2
 **/
#define BE_DEBUG_DUMP_LEVEL             2

/* Macro: BE_STACK_TOTAL_MAX
 * Set the maximum total stack size.
 * default: 2000
 **/
#define BE_STACK_TOTAL_MAX              2000

/* Macro: BE_STACK_FREE_MIN
 * Set the minimum free count of the stack. The stack idles will
 * be checked when a function is called, and the stack will be
 * expanded if the number of free is less than BE_STACK_FREE_MIN.
 * default: 10
 **/
#define BE_STACK_FREE_MIN               10

/*
 * Macro: BE_STACK_FREE_MIN
 * The short string will hold the hash value when the value is
 * true. It may be faster but requires more RAM.
 * default: 0
 **/
#define BE_STR_HASH_CACHE               0

/*
 * Macro: BE_USE_FILE_SYSTEM
 * The file system interface will be used when this macro is true
 * or when using the OS module. Otherwise the file system interface
 * will not be used.
 * default: 0
 **/
#define BE_USE_FILE_SYSTEM              0

/* Macro: BE_USE_XXX_MODULE
 * These macros control whether the related module is compiled.
 * When they are true, they will enable related modules. At this
 * point you can use the import statement to import the module.
 * They will not compile related modules when they are false.
 **/
#define BE_USE_STRING_MODULE            1
#define BE_USE_JSON_MODULE              1
#define BE_USE_MATH_MODULE              1
#define BE_USE_TIME_MODULE              1
#define BE_USE_OS_MODULE                1

/* Macro: BE_EXPLICIT_XXX
 * If these macros are defined, the corresponding function will
 * use the version defined by these macros. These macro definitions
 * are not required.
 * The default is to use the functions in the standard library.
 */
#define BE_EXPLICIT_ABORT               abort
#define BE_EXPLICIT_EXIT                exit
#define BE_EXPLICIT_MALLOC              malloc
#define BE_EXPLICIT_FREE                free
#define BE_EXPLICIT_REALLOC             realloc

/* Macro: be_assert
 * Berry debug assertion. Only enabled when BE_DEBUG is active.
 * default: use the assert() function of the standard library.
 **/
#define be_assert(expr)                 assert(expr)

#endif
