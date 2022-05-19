#include "be_object.h"

#define map_check_data(vm, argc)                        \
    if (!be_ismap(vm, -1) || be_top(vm) - 1 < argc) {   \
        be_return_nil(vm);                              \
    }

#define map_check_ref(vm)                               \
    if (be_refcontains(vm, 1)) {                        \
        be_pushstring(vm, "{...}");                     \
        be_return(vm);                                  \
    }

static int m_init(bvm *vm)
{
    if (be_top(vm) > 1 && be_ismap(vm, 2)) {
        be_pushvalue(vm, 2);
        be_setmember(vm, 1, ".data");
    } else {
        be_newmap(vm);
        be_setmember(vm, 1, ".data");
    }
    be_return_nil(vm);
}

static void push_key(bvm *vm)
{
    if (be_isstring(vm, -2)) { /* add ''' to strings */
        be_pushfstring(vm, "'%s'", be_tostring(vm, -2));
    } else {
        be_tostring(vm, -2);
        be_pushvalue(vm, -2); /* push to top */
    }
    be_strconcat(vm, -5);
    be_pop(vm, 1);
}

static void push_value(bvm *vm)
{
    if (be_isstring(vm, -1)) { /* add ''' to strings */
        be_pushfstring(vm, "'%s'", be_tostring(vm, -1));
    } else {
        be_tostring(vm, -1);
        be_pushvalue(vm, -1); /* push to top */
    }
    be_strconcat(vm, -5);
    be_pop(vm, 3);
    if (be_iter_hasnext(vm, -3)) {
        be_pushstring(vm, ", ");
        be_strconcat(vm, -3);
        be_pop(vm, 1);
    }
}

static int m_tostring(bvm *vm)
{
    be_getmember(vm, 1, ".data");
    map_check_data(vm, 1);
    map_check_ref(vm);
    be_refpush(vm, 1);
    be_pushstring(vm, "{");
    be_pushiter(vm, -2); /* map iterator use 1 register */
    while (be_iter_hasnext(vm, -3)) {
        be_iter_next(vm, -3);
        push_key(vm); /* key.tostring() */
        be_pushstring(vm, ": "); /* add ': ' */
        be_strconcat(vm, -5);
        be_pop(vm, 1);
        push_value(vm); /* value.tostring() */
    }
    be_pop(vm, 1); /* pop iterator */
    be_pushstring(vm, "}");
    be_strconcat(vm, -2);
    be_pop(vm, 1);
    be_refpop(vm);
    be_return(vm);
}

static int m_insert(bvm *vm)
{
    be_getmember(vm, 1, ".data");
    map_check_data(vm, 3);
    be_pushvalue(vm, 2);
    be_pushvalue(vm, 3);
    be_data_insert(vm, -3);
    be_return_nil(vm);
}

static int m_remove(bvm *vm)
{
    be_getmember(vm, 1, ".data");
    map_check_data(vm, 2);
    be_pushvalue(vm, 2);
    be_data_remove(vm, -2);
    be_return_nil(vm);
}

static int m_item(bvm *vm)
{
    be_getmember(vm, 1, ".data");
    map_check_data(vm, 2);
    be_pushvalue(vm, 2);
    be_getindex(vm, -2);
    be_return(vm);
}

static int m_setitem(bvm *vm)
{
    be_getmember(vm, 1, ".data");
    map_check_data(vm, 3);
    be_pushvalue(vm, 2);
    be_pushvalue(vm, 3);
    be_setindex(vm, -3);
    be_return_nil(vm);
}

static int m_size(bvm *vm)
{
    be_getmember(vm, 1, ".data");
    map_check_data(vm, 1);
    be_pushint(vm, be_data_size(vm, -1));
    be_return(vm);
}

static int i_init(bvm *vm)
{
    be_pushvalue(vm, 2);
    be_setmember(vm, 1, ".obj");
    be_pop(vm, 1);
    be_getmember(vm, 2, ".data");
    be_pushiter(vm, -1);
    be_setmember(vm, 1, ".iter");
    be_return_nil(vm);
}

static int i_hashnext(bvm *vm)
{
    be_getmember(vm, 1, ".obj");
    be_getmember(vm, -1, ".data");
    be_getmember(vm, 1, ".iter");
    be_pushbool(vm, be_iter_hasnext(vm, -2));
    be_return(vm);
}

static int i_next(bvm *vm)
{
    be_getmember(vm, 1, ".obj");
    be_getmember(vm, -1, ".data");
    be_getmember(vm, 1, ".iter");
    be_iter_next(vm, -2); /* map next key and value */
    be_pushvalue(vm, -3); /* push .iter to top */
    be_setmember(vm, 1, ".iter");
    be_pop(vm, 1);
    be_return(vm); /* return value */
}

static int m_iter(bvm *vm)
{
    static const bnfuncinfo members[] = {
        { ".obj", NULL },
        { ".iter", NULL },
        { "init", i_init },
        { "hasnext", i_hashnext },
        { "next", i_next },
        { NULL, NULL }
    };
    be_pushclass(vm, "iterator", members);
    be_pushvalue(vm, 1);
    be_call(vm, 1);
    be_pop(vm, 1);
    be_return(vm);
}

#if !BE_USE_PRECOMPILED_OBJECT
void be_load_maplib(bvm *vm)
{
    static const bnfuncinfo members[] = {
        { ".data", NULL },
        { "init", m_init },
        { "tostring", m_tostring },
        { "insert", m_insert },
        { "remove", m_remove },
        { "item", m_item },
        { "setitem", m_setitem },
        { "size", m_size },
        { "iter", m_iter },
        { NULL, NULL }
    };
    be_regclass(vm, "map", members);
}
#else
/* @const_object_info_begin
class be_class_map (scope: global, name: map) {
    .data, var
    init, func(m_init)
    tostring, func(m_tostring)
    insert, func(m_insert)
    remove, func(m_remove)
    item, func(m_item)
    setitem, func(m_setitem)
    size, func(m_size)
    iter, func(m_iter)
}
@const_object_info_end */
#include "../generate/be_fixed_be_class_map.h"
#endif
