#include "be_constobj.h"

static const bmapnode m_builtin_map_slots[] = {
    { be_const_key(be_const_str_size, 2), be_const_int(19) },
    { be_const_key(be_const_str_map, -1), be_const_int(12) },
    { be_const_key(be_const_str_number, -1), be_const_int(14) },
    { be_const_key(be_const_str_type, 5), be_const_int(22) },
    { be_const_key(be_const_str_int, 21), be_const_int(10) },
    { be_const_key(be_const_str_classname, -1), be_const_int(4) },
    { be_const_key(be_const_str_print, 19), be_const_int(16) },
    { be_const_key(be_const_str_memcount, -1), be_const_int(13) },
    { be_const_key(be_const_str_assert, -1), be_const_int(3) },
    { be_const_key(be_const_str_list, -1), be_const_int(11) },
    { be_const_key(be_const_str___iterator__, -1), be_const_int(1) },
    { be_const_key(be_const_str_codedump, 12), be_const_int(6) },
    { be_const_key(be_const_str___hasnext__, 20), be_const_int(0) },
    { be_const_key(be_const_str_exit, 8), be_const_int(8) },
    { be_const_key(be_const_str_classof, 4), be_const_int(5) },
    { be_const_key(be_const_str_input, -1), be_const_int(9) },
    { be_const_key(be_const_str_compile, -1), be_const_int(7) },
    { be_const_key(be_const_str___next__, 16), be_const_int(2) },
    { be_const_key(be_const_str_open, -1), be_const_int(15) },
    { be_const_key(be_const_str_range, -1), be_const_int(17) },
    { be_const_key(be_const_str_real, -1), be_const_int(18) },
    { be_const_key(be_const_str_super, 22), be_const_int(21) },
    { be_const_key(be_const_str_str, -1), be_const_int(20) },
};

static const bmap m_builtin_map = {
    be_const_header_map(),
    .slots = (bmapnode *)m_builtin_map_slots,
    .lastfree = (bmapnode *)&m_builtin_map_slots[22],
    .size = 23,
    .count = 23
};

static const bvalue __vlist_array[] = {
    be_const_func(l_hasnext),
    be_const_func(l_iterator),
    be_const_func(l_next),
    be_const_func(l_assert),
    be_const_func(l_classname),
    be_const_func(l_classof),
    be_const_func(l_codedump),
    be_const_func(l_compile),
    be_const_func(l_exit),
    be_const_func(l_input),
    be_const_func(l_int),
    be_const_class(be_class_list),
    be_const_class(be_class_map),
    be_const_func(l_memcount),
    be_const_func(l_number),
    be_const_func(be_nfunc_open),
    be_const_func(l_print),
    be_const_class(be_class_range),
    be_const_func(l_real),
    be_const_func(l_size),
    be_const_func(l_str),
    be_const_func(l_super),
    be_const_func(l_type),
};

static const bvector m_builtin_vector = {
    .capacity = 23, .size = sizeof(bvalue),
    .data = (void*)__vlist_array,
    .end = (void*)(__vlist_array + 22)
};
