/* -*- mode: C++; coding: utf-8 -*- */
/*
* UUIDValue.hpp
*
* Copyright (c) 2016 Masashi Fujita
*/
#pragma once

#ifndef uuidvalue_hpp__A30DB45C_2AED_45D5_8851_CC2CB212A14E
#define uuidvalue_hpp__A30DB45C_2AED_45D5_8851_CC2CB212A14E 1

#include <sys/types.h>
#include <stdint.h>
#include <array>
#include <string>

namespace UUIDValue {
    using uuid_t = std::array<uint8_t, 16> ;

    uuid_t  NewUUID () ;

    std::string ToString (const uuid_t &uuid) ;
}

#endif	/* uuidvalue_hpp__A30DB45C_2AED_45D5_8851_CC2CB212A14E */
