#include "be_constobj.h"

static const bmapnode m_libtime_map_slots[] = {
    { be_const_key(be_const_str_dump, 1), be_const_func(m_dump) },
    { be_const_key(be_const_str_clock, -1), be_const_func(m_clock) },
    { be_const_key(be_const_str_time, 0), be_const_func(m_time) },
};

static const bmap m_libtime_map = {
    be_const_header_map(),
    .slots = (bmapnode *)m_libtime_map_slots,
    .lastfree = (bmapnode *)&m_libtime_map_slots[2],
    .size = 3,
    .count = 3
};

static const bmodule m_libtime = {
    be_const_header_module(),
    .table = (bmap*)&m_libtime_map,
    .info.name = "time",
    .mnext = NULL
};

be_define_const_module(time);
