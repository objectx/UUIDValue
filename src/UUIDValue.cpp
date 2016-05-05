/* -*- mode: c++; coding: utf-8 -*- */
/*
 * UUIDValue.cpp:
 *
 * Copyright (c) 2016 Masashi Fujita
 */

#include <sys/types.h>
#include <stdint.h>

#include <random>

#include "UUIDValue.hpp"

namespace {
    std::random_device   random_dev ;
}

namespace UUIDValue {

    uuid_t  NewUUID () {

        std::uniform_int_distribution<unsigned long>    dist ;

        auto v0 = dist (random_dev) ;
        auto v1 = dist (random_dev) ;

        // xxxxxxxx-xxxx-4xxxx-Yxxxx-xxxxxxxxxxxx (Y = 8, 9, A, B)
        return uuid_t { { static_cast<uint8_t> (v0 >>  0)
                        , static_cast<uint8_t> (v0 >>  8)
                        , static_cast<uint8_t> (v0 >> 16)
                        , static_cast<uint8_t> (v0 >> 24)
                        , static_cast<uint8_t> (v0 >> 32)
                        , static_cast<uint8_t> (v0 >> 40)
                        , static_cast<uint8_t> (((v0 >> 48) & 0x0Fu) | 0x40u)
                        , static_cast<uint8_t> (v0 >> 56)
                        , static_cast<uint8_t> (((v1 >>  0) & ~0x40u) | 0x80u)
                        , static_cast<uint8_t> (v1 >>  8)
                        , static_cast<uint8_t> (v1 >> 16)
                        , static_cast<uint8_t> (v1 >> 24)
                        , static_cast<uint8_t> (v1 >> 32)
                        , static_cast<uint8_t> (v1 >> 40)
                        , static_cast<uint8_t> (v1 >> 48)
                        , static_cast<uint8_t> (v1 >> 56) } } ;
    }

    std::string ToString (const uuid_t &uuid) {
        static const char   digits [] = { '0', '1', '2', '3'
                                        , '4', '5', '6', '7'
                                        , '8', '9', 'a', 'b'
                                        , 'c', 'd', 'e', 'f' } ;
        std::string result ;
        result.reserve (2 * uuid.size ()) ;

        for (auto v : uuid) {
            result.push_back (digits [(v >> 4) & 0x0Fu]) ;
            result.push_back (digits [(v >> 0) & 0x0Fu]) ;
        }
        return result ;
    }
}
