/* -*- c++ -*- */
/*
 * Copyright 2026 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "pagesize.h"
#include "vmcircbuf_emulated.h"
#include <algorithm>
#include <cstring>
#include <limits>
#include <stdexcept>

namespace gr {

vmcircbuf_emulated::vmcircbuf_emulated(size_t size) : gr::vmcircbuf(size)
{
    if (size == 0 || size > std::numeric_limits<size_t>::max() / 2) {
        throw std::invalid_argument("gr::vmcircbuf_emulated: invalid size");
    }

    d_storage = std::make_unique<char[]>(2 * size);
    std::memset(d_storage.get(), 0, 2 * size);
    d_base = d_storage.get();
}

vmcircbuf_emulated::~vmcircbuf_emulated() = default;

void vmcircbuf_emulated::commit_write(size_t offset, size_t size)
{
    if (size == 0) {
        return;
    }
    if (offset >= d_size || size > d_size || size > (2 * d_size) - offset) {
        throw std::out_of_range("gr::vmcircbuf_emulated: write outside circular view");
    }

    const size_t tail_size = std::min(size, d_size - offset);
    std::memcpy(d_base + d_size + offset, d_base + offset, tail_size);

    const size_t wrapped_size = size - tail_size;
    if (wrapped_size != 0) {
        std::memcpy(d_base, d_base + d_size, wrapped_size);
    }
}

gr::vmcircbuf_factory* vmcircbuf_emulated_factory::s_the_factory = nullptr;

gr::vmcircbuf_factory* vmcircbuf_emulated_factory::singleton()
{
    if (!s_the_factory) {
        s_the_factory = new gr::vmcircbuf_emulated_factory();
    }
    return s_the_factory;
}

int vmcircbuf_emulated_factory::granularity() { return gr::pagesize(); }

gr::vmcircbuf* vmcircbuf_emulated_factory::make(size_t size)
{
    try {
        return new vmcircbuf_emulated(size);
    } catch (...) {
        return nullptr;
    }
}

} // namespace gr
