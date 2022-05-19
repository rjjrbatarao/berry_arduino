#include "be_object.h"
#include "be_mem.h"
#include <string.h>

#define READLINE_STEP       100

static int l_assert(bvm *vm)
{
    int argc = be_top(vm);
    /* assertion fails when there is no argument
     * or the first argument is nil or false. */
    if (!argc || !be_tobool(vm, 1)) {
        const char *msg = "assert failed!";
        if (argc >= 2 && be_isstring(vm, 2)) {
            msg = be_tostring(vm, 2);
        }
        be_pusherror(vm, msg);
    }
    be_return_nil(vm);
}

static int l_print(bvm *vm)
{
    int i, argc = be_top(vm);
    for (i = 1; i <= argc; ++i) {
        const char *str = be_tostring(vm, i);
        size_t len = be_strlen(vm, i);
        be_writebuffer(str, len);
        if (i < argc) {
            be_writebuffer(" ", 1);
        }
    }
    be_writenewline();
    be_return_nil(vm);
}

static int m_readline(bvm *vm)
{
    size_t pos = 0, size = READLINE_STEP;
    char *buffer = be_malloc(vm, size);
    char *res = be_readstring(buffer, (int)size);
    while (res) {
        pos += strlen(buffer + pos) - 1;
        if (!pos || buffer[pos] == '\n') {
            break;
        }
        buffer = be_realloc(vm, buffer, size, size + READLINE_STEP);
        res = be_readstring(buffer + pos + 1, READLINE_STEP);
        size += READLINE_STEP;
    }
    be_pushstring(vm, buffer);
    be_free(vm, buffer, size);
    be_return(vm);
}

static int l_input(bvm *vm)
{
    if (be_top(vm) && be_isstring(vm, 1)) { /* echo prompt */
        be_writestring(be_tostring(vm, 1));
    }
    return m_readline(vm);
}

static int l_exit(bvm *vm)
{
    int status = 0;
    if (be_top(vm) && be_isint(vm, -1)) {
        status = be_toindex(vm, -1);
    }
    be_exit(vm, status);
    be_return_nil(vm);
}

static int l_memcount(bvm *vm)
{
    size_t count = be_memcount(vm);
    if (count < 0x80000000) {
        be_pushint(vm, (bint)count);
    } else {
        be_pushreal(vm, (breal)count);
    }
    be_return(vm);
}

static int l_super(bvm *vm)
{
    if (be_top(vm)) {
        be_getsuper(vm, 1);
        be_return(vm);
    }
    be_return_nil(vm);
}

static int l_type(bvm *vm)
{
    if (be_top(vm)) {
        be_pushstring(vm, be_typename(vm, 1));
        be_return(vm);
    }
    be_return_nil(vm);
}

static int l_classname(bvm *vm)
{
    if (be_top(vm)) {
        const char *t = be_classname(vm, 1);
        if (t) {
            be_pushstring(vm, t);
            be_return(vm);
        }
    }
    be_return_nil(vm);
}

static int l_classof(bvm *vm)
{
    if (be_top(vm) && !be_classof(vm, 1)) {
        be_return(vm);
    }
    be_return_nil(vm);
}

static int l_number(bvm *vm)
{
    if (be_top(vm)) {
        if (be_isstring(vm, 1)) {
            be_str2num(vm, be_tostring(vm, 1));
            be_return(vm);
        } else if (be_isnumber(vm, 1)) {
            be_pushvalue(vm, 1);
            be_return(vm);
        }
    }
    be_return_nil(vm);
}

static int l_int(bvm *vm)
{
    if (be_top(vm)) {
        if (be_isstring(vm, 1)) {
            const char *s = be_tostring(vm, 1);
            be_pushint(vm, be_str2int(s, NULL));
        } else if (be_isreal(vm, 1)) {
            be_pushint(vm, (bint)be_toreal(vm, 1));
        } else if (be_isint(vm, 1)) {
            be_pushvalue(vm, 1);
        } else {
            be_return_nil(vm);
        }
        be_return(vm);
    }
    be_return_nil(vm);
}

static int l_real(bvm *vm)
{
    if (be_top(vm)) {
        if (be_isstring(vm, 1)) {
            const char *s = be_tostring(vm, 1);
            be_pushreal(vm, be_str2real(s, NULL));
        } else if (be_isint(vm, 1)) {
            be_pushreal(vm, (breal)be_toint(vm, 1));
        } else if (be_isreal(vm, 1)) {
            be_pushvalue(vm, 1);
        } else {
            be_return_nil(vm);
        }
        be_return(vm);
    }
    be_return_nil(vm);
}

static int check_method(bvm *vm, const char *attr)
{
    return be_top(vm) &&
        be_isinstance(vm, 1) && be_getmethod(vm, 1, attr);
}

static int l_iterator(bvm *vm)
{
    if (check_method(vm, "iter")) {
        be_pushvalue(vm, 1);
        be_call(vm, 1);
        be_pop(vm, 1);
        be_return(vm);
    }
    be_return_nil(vm);
}

static int l_hasnext(bvm *vm)
{
    if (check_method(vm, "hasnext")) {
        be_pushvalue(vm, 1);
        be_call(vm, 1);
        be_pop(vm, 1);
    } else {
        be_pushbool(vm, bfalse);
    }
    be_return(vm);
}

static int l_next(bvm *vm)
{
    if (check_method(vm, "next")) {
        be_pushvalue(vm, 1);
        be_call(vm, 1);
        be_pop(vm, 1);
        be_return(vm);
    }
    be_return_nil(vm);
}

static int l_str(bvm *vm)
{
    if (be_top(vm)) {
        be_tostring(vm, 1);
    } else {
        be_pushstring(vm, "");
    }
    be_return(vm);
}

static int l_size(bvm *vm)
{
    if (be_top(vm) && be_isstring(vm, 1)) {
        be_pushint(vm, be_strlen(vm, 1));
        be_return(vm);
    }
    if (check_method(vm, "size")) {
        be_pushvalue(vm, 1);
        be_call(vm, 1);
        be_pop(vm, 1);
        be_return(vm);
    }
    be_return_nil(vm);
}

static int m_compile_str(bvm *vm)
{
    int len = be_strlen(vm, 1);
    const char *src = be_tostring(vm, 1);
    int res = be_loadbuffer(vm, "string", src, len);
    if (res == BE_OK) {
        be_return(vm);
    }
    be_return_nil(vm);
}

static int m_compile_file(bvm *vm)
{
    const char *fname = be_tostring(vm, 1);
    int res = be_loadfile(vm, fname);
    if (res == BE_OK) {
        be_return(vm);
    }
    be_return_nil(vm);
}

static int l_compile(bvm *vm)
{
    if (be_top(vm) && be_isstring(vm, 1)) {
        if (be_top(vm) >= 2 && be_isstring(vm, 2)) {
            const char *s = be_tostring(vm, 2);
            if (!strcmp(s, "string")) {
                return m_compile_str(vm);
            }
            if (!strcmp(s, "file")) {
                return m_compile_file(vm);
            }
        } else {
            return m_compile_str(vm);
        }
    }
    be_return_nil(vm);
}

static int l_codedump(bvm *vm)
{
    if (be_top(vm) >= 1) {
        be_codedump(vm, 1);
    }
    be_return_nil(vm);
}

#if !BE_USE_PRECOMPILED_OBJECT
void be_load_baselib(bvm *vm)
{
    be_regfunc(vm, "assert", l_assert);
    be_regfunc(vm, "print", l_print);
    be_regfunc(vm, "input", l_input);
    be_regfunc(vm, "exit", l_exit);
    be_regfunc(vm, "super", l_super);
    be_regfunc(vm, "memcount", l_memcount);
    be_regfunc(vm, "type", l_type);
    be_regfunc(vm, "classname", l_classname);
    be_regfunc(vm, "classof", l_classof);
    be_regfunc(vm, "number", l_number);
    be_regfunc(vm, "str", l_str);
    be_regfunc(vm, "int", l_int);
    be_regfunc(vm, "real", l_real);
    be_regfunc(vm, "size", l_size);
    be_regfunc(vm, "compile", l_compile);
    be_regfunc(vm, "codedump", l_codedump);
    be_regfunc(vm, "__iterator__", l_iterator);
    be_regfunc(vm, "__hasnext__", l_hasnext);
    be_regfunc(vm, "__next__", l_next);
}
#else
extern const bclass be_class_list;
extern const bclass be_class_map;
extern const bclass be_class_range;
extern int be_nfunc_open(bvm *vm);
/* @const_object_info_begin
vartab m_builtin (scope: local) {
    assert, func(l_assert)
    print, func(l_print)
    input, func(l_input)
    exit, func(l_exit)
    super, func(l_super)
    memcount, func(l_memcount)
    type, func(l_type)
    classname, func(l_classname)
    classof, func(l_classof)
    number, func(l_number)
    str, func(l_str)
    int, func(l_int)
    real, func(l_real)
    size, func(l_size)
    compile, func(l_compile)
    codedump, func(l_codedump)
    __iterator__, func(l_iterator)
    __hasnext__, func(l_hasnext)
    __next__, func(l_next)
    open, func(be_nfunc_open)
    list, class(be_class_list)
    map, class(be_class_map)
    range, class(be_class_range)
}
@const_object_info_end */
#include "../generate/be_fixed_m_builtin.h"
#include "be_var.h"

void be_load_baselib(bvm *vm)
{
    be_const_builtin_set(vm, &m_builtin_map, &m_builtin_vector);
}
#endif
