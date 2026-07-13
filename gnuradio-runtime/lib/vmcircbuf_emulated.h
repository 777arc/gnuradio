/* -*- c++ -*- */
/*
 * Copyright 2026 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_GR_VMCIRCBUF_EMULATED_H
#define INCLUDED_GR_VMCIRCBUF_EMULATED_H

#include "vmcircbuf.h"
#include <memory>

namespace gr {

/*!
 * \brief Software-emulated double-mapped circular buffer.
 *
 * This backend reserves two adjacent physical copies. Writes are made through the
 * same contiguous 2N-byte view as a native vmcircbuf, then commit_write() restores
 * coherence before the write is published to readers.
 */
class vmcircbuf_emulated : public gr::vmcircbuf
{
public:
    explicit vmcircbuf_emulated(size_t size);
    ~vmcircbuf_emulated() override;

    void commit_write(size_t offset, size_t size) override;

private:
    std::unique_ptr<char[]> d_storage;
};

class vmcircbuf_emulated_factory : public gr::vmcircbuf_factory
{
public:
    static vmcircbuf_factory* singleton();

    const char* name() const override { return "gr::vmcircbuf_emulated_factory"; }
    int granularity() override;
    gr::vmcircbuf* make(size_t size) override;

private:
    static vmcircbuf_factory* s_the_factory;
};

} // namespace gr

#endif /* INCLUDED_GR_VMCIRCBUF_EMULATED_H */
