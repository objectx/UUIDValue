#
# Copyright (c) 2016 Masashi Fujita
#

cmake_minimum_required (VERSION 3.5)

project (UUIDVALUE
         LANGUAGES CXX C
         VERSION 1.0.0.0)

list (INSERT CMAKE_MODULE_PATH 0 "${CMAKE_CURRENT_SOURCE_DIR}/CMake")

function (setvar_default var_)
    if (NOT DEFINED ${var_})
        set (${var_} ${ARGN} PARENT_SCOPE)
    endif ()
endfunction ()

enable_testing ()

include (cotire OPTIONAL)

setvar_default (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
setvar_default (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
setvar_default (CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

include_directories (${CMAKE_CURRENT_BINARY_DIR})

set (UUIDVALUE_SOURCES src/UUIDValue.cpp)
set (UUIDVALUE_HEADERS include/UUIDValue.hpp)

add_library (UUIDValue ${UUIDVALUE_SOURCES} ${UUIDVALUE_HEADERS})
    target_include_directories (UUIDValue PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include>)
    target_compile_features (UUIDValue PUBLIC cxx_auto_type)

if (COMMAND cotire)
    cotire (UUIDValue)
endif ()

add_subdirectory (test)
