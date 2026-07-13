/* -*- c++ -*- */
/*
 * Copyright 2002,2013,2018 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "vmcircbuf.h"
#include "vmcircbuf_emulated.h"
#include <boost/test/unit_test.hpp>
#include <cstdint>
#include <memory>

BOOST_AUTO_TEST_CASE(test_all)
{
    int verbose = 1; // summary

    BOOST_REQUIRE(gr::vmcircbuf_sysconfig::test_all_factories(verbose));
}

BOOST_AUTO_TEST_CASE(test_emulated_factory)
{
    auto* factory = gr::vmcircbuf_emulated_factory::singleton();
    BOOST_REQUIRE(gr::vmcircbuf_sysconfig::test_factory(factory, 1));

    constexpr size_t size = 4096;
    std::unique_ptr<gr::vmcircbuf> buffer(factory->make(size));
    BOOST_REQUIRE(buffer);

    auto* first = static_cast<std::uint8_t*>(buffer->pointer_to_first_copy());
    auto* second = static_cast<std::uint8_t*>(buffer->pointer_to_second_copy());
    for (size_t i = 0; i < size; ++i) {
        first[i] = static_cast<std::uint8_t>(i);
    }
    buffer->commit_write(0, size);

    constexpr size_t offset = size - 16;
    constexpr size_t write_size = 32;
    for (size_t i = 0; i < write_size; ++i) {
        first[offset + i] = static_cast<std::uint8_t>(0xa0 + i);
    }
    buffer->commit_write(offset, write_size);

    for (size_t i = 0; i < size; ++i) {
        BOOST_CHECK_EQUAL(first[i], second[i]);
    }
}
