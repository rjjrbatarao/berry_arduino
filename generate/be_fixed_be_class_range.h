#include "be_constobj.h"

static const bmapnode be_class_range_map_slots[] = {
    { be_const_key(be_const_str_setrange, -1), be_const_func(m_setrange) },
    { be_const_key(be_const_str_iter, -1), be_const_func(m_iter) },
    { be_const_key(be_const_str_lower, -1), be_const_func(m_lower) },
    { be_const_key(be_const_str_init, 4), be_const_func(m_init) },
    { be_const_key(be_const_str___upper__, -1), be_const_int(0) },
    { be_const_key(be_const_str_tostring, -1), be_const_func(m_tostring) },
    { be_const_key(be_const_str___lower__, -1), be_const_int(1) },
    { be_const_key(be_const_str_upper, 1), be_const_func(m_upper) },
};

static const bmap be_class_range_map = {
    be_const_header_map(),
    .slots = (bmapnode *)be_class_range_map_slots,
    .lastfree = (bmapnode *)&be_class_range_map_slots[7],
    .size = 8,
    .count = 8
};

const bclass be_class_range = {
    be_const_header_class(),
    .nvar = 2,
    .super = NULL,
    .members = (bmap *)&be_class_range_map,
    .name = (bstring *)&be_const_str_range
};
