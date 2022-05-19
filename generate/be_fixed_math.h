#include "be_constobj.h"

static const bmapnode m_libmath_map_slots[] = {
    { be_const_key(be_const_str_pi, 2), be_const_real(M_PI) },
    { be_const_key(be_const_str_acos, -1), be_const_func(m_acos) },
    { be_const_key(be_const_str_tan, -1), be_const_func(m_tan) },
    { be_const_key(be_const_str_floor, 6), be_const_func(m_floor) },
    { be_const_key(be_const_str_log10, -1), be_const_func(m_log10) },
    { be_const_key(be_const_str_sqrt, -1), be_const_func(m_sqrt) },
    { be_const_key(be_const_str_deg, -1), be_const_func(m_deg) },
    { be_const_key(be_const_str_cos, -1), be_const_func(m_cos) },
    { be_const_key(be_const_str_atan, -1), be_const_func(m_atan) },
    { be_const_key(be_const_str_sinh, -1), be_const_func(m_sinh) },
    { be_const_key(be_const_str_tanh, -1), be_const_func(m_tanh) },
    { be_const_key(be_const_str_pow, -1), be_const_func(m_pow) },
    { be_const_key(be_const_str_rad, 13), be_const_func(m_rad) },
    { be_const_key(be_const_str_exp, -1), be_const_func(m_exp) },
    { be_const_key(be_const_str_asin, 7), be_const_func(m_asin) },
    { be_const_key(be_const_str_log, 8), be_const_func(m_log) },
    { be_const_key(be_const_str_ceil, -1), be_const_func(m_ceil) },
    { be_const_key(be_const_str_sin, 3), be_const_func(m_sin) },
    { be_const_key(be_const_str_rand, -1), be_const_func(m_rand) },
    { be_const_key(be_const_str_srand, 1), be_const_func(m_srand) },
    { be_const_key(be_const_str_cosh, -1), be_const_func(m_cosh) },
    { be_const_key(be_const_str_abs, -1), be_const_func(m_abs) },
};

static const bmap m_libmath_map = {
    be_const_header_map(),
    .slots = (bmapnode *)m_libmath_map_slots,
    .lastfree = (bmapnode *)&m_libmath_map_slots[21],
    .size = 22,
    .count = 22
};

static const bmodule m_libmath = {
    be_const_header_module(),
    .table = (bmap*)&m_libmath_map,
    .info.name = "math",
    .mnext = NULL
};

be_define_const_module(math);
