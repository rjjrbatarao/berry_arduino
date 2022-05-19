#include "be_constobj.h"

static const bmapnode m_libos_map_slots[] = {
    { be_const_key(be_const_str_mkdir, 5), be_const_func(m_mkdir) },
    { be_const_key(be_const_str_remove, 2), be_const_func(m_remove) },
    { be_const_key(be_const_str_path, -1), be_const_module(m_libpath) },
    { be_const_key(be_const_str_chdir, -1), be_const_func(m_chdir) },
    { be_const_key(be_const_str_getcwd, -1), be_const_func(m_getcwd) },
    { be_const_key(be_const_str_system, -1), be_const_func(m_system) },
    { be_const_key(be_const_str_listdir, -1), be_const_func(m_listdir) },
};

static const bmap m_libos_map = {
    be_const_header_map(),
    .slots = (bmapnode *)m_libos_map_slots,
    .lastfree = (bmapnode *)&m_libos_map_slots[6],
    .size = 7,
    .count = 7
};

static const bmodule m_libos = {
    be_const_header_module(),
    .table = (bmap*)&m_libos_map,
    .info.name = "os",
    .mnext = NULL
};

be_define_const_module(os);
