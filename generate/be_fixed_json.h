#include "be_constobj.h"

static const bmapnode m_libjson_map_slots[] = {
    { be_const_key(be_const_str_dump, -1), be_const_func(m_json_dump) },
    { be_const_key(be_const_str_load, 0), be_const_func(m_json_load) },
};

static const bmap m_libjson_map = {
    be_const_header_map(),
    .slots = (bmapnode *)m_libjson_map_slots,
    .lastfree = (bmapnode *)&m_libjson_map_slots[1],
    .size = 2,
    .count = 2
};

static const bmodule m_libjson = {
    be_const_header_module(),
    .table = (bmap*)&m_libjson_map,
    .info.name = "json",
    .mnext = NULL
};

be_define_const_module(json);
