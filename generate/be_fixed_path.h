#include "be_constobj.h"

static const bmapnode m_libpath_map_slots[] = {
    { be_const_key(be_const_str_isdir, -1), be_const_func(m_isdir) },
    { be_const_key(be_const_str_exists, -1), be_const_func(m_exists) },
    { be_const_key(be_const_str_splitext, -1), be_const_func(m_splitext) },
    { be_const_key(be_const_str_isfile, -1), be_const_func(m_isfile) },
};

static const bmap m_libpath_map = {
    be_const_header_map(),
    .slots = (bmapnode *)m_libpath_map_slots,
    .lastfree = (bmapnode *)&m_libpath_map_slots[3],
    .size = 4,
    .count = 4
};

static const bmodule m_libpath = {
    be_const_header_module(),
    .table = (bmap*)&m_libpath_map,
    .info.name = "path",
    .mnext = NULL
};
