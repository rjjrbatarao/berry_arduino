#include "be_constobj.h"

static const bmapnode m_libstring_map_slots[] = {
    { be_const_key(be_const_str_format, -1), be_const_func(str_format) },
};

static const bmap m_libstring_map = {
    be_const_header_map(),
    .slots = (bmapnode *)m_libstring_map_slots,
    .lastfree = (bmapnode *)&m_libstring_map_slots[0],
    .size = 1,
    .count = 1
};

static const bmodule m_libstring = {
    be_const_header_module(),
    .table = (bmap*)&m_libstring_map,
    .info.name = "string",
    .mnext = NULL
};

be_define_const_module(string);
