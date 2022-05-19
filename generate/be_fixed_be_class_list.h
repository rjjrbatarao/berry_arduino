#include "be_constobj.h"

static const bmapnode be_class_list_map_slots[] = {
    { be_const_key(be_const_str_resize, -1), be_const_func(m_resize) },
    { be_const_key(be_const_str_insert, -1), be_const_func(m_insert) },
    { be_const_key(be_const_str_init, -1), be_const_func(m_init) },
    { be_const_key(be_const_str_tostring, -1), be_const_func(m_tostring) },
    { be_const_key(be_const_str_iter, 5), be_const_func(m_iter) },
    { be_const_key(be_const_str_size, -1), be_const_func(m_size) },
    { be_const_key(be_const_str_dot_data, 0), be_const_int(0) },
    { be_const_key(be_const_str_setitem, -1), be_const_func(m_setitem) },
    { be_const_key(be_const_str_remove, -1), be_const_func(m_remove) },
    { be_const_key(be_const_str_append, 2), be_const_func(m_append) },
    { be_const_key(be_const_str_item, 1), be_const_func(m_item) },
};

static const bmap be_class_list_map = {
    be_const_header_map(),
    .slots = (bmapnode *)be_class_list_map_slots,
    .lastfree = (bmapnode *)&be_class_list_map_slots[10],
    .size = 11,
    .count = 11
};

const bclass be_class_list = {
    be_const_header_class(),
    .nvar = 1,
    .super = NULL,
    .members = (bmap *)&be_class_list_map,
    .name = (bstring *)&be_const_str_list
};
