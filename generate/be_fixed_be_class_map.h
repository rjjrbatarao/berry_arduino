#include "be_constobj.h"

static const bmapnode be_class_map_map_slots[] = {
    { be_const_key(be_const_str_size, -1), be_const_func(m_size) },
    { be_const_key(be_const_str_iter, -1), be_const_func(m_iter) },
    { be_const_key(be_const_str_setitem, -1), be_const_func(m_setitem) },
    { be_const_key(be_const_str_remove, -1), be_const_func(m_remove) },
    { be_const_key(be_const_str_item, 1), be_const_func(m_item) },
    { be_const_key(be_const_str_dot_data, 2), be_const_int(0) },
    { be_const_key(be_const_str_init, -1), be_const_func(m_init) },
    { be_const_key(be_const_str_tostring, -1), be_const_func(m_tostring) },
    { be_const_key(be_const_str_insert, -1), be_const_func(m_insert) },
};

static const bmap be_class_map_map = {
    be_const_header_map(),
    .slots = (bmapnode *)be_class_map_map_slots,
    .lastfree = (bmapnode *)&be_class_map_map_slots[8],
    .size = 9,
    .count = 9
};

const bclass be_class_map = {
    be_const_header_class(),
    .nvar = 1,
    .super = NULL,
    .members = (bmap *)&be_class_map_map,
    .name = (bstring *)&be_const_str_map
};
