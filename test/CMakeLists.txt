
cmake_minimum_required (VERSION 3.5)

set (SOURCE_FILES UUIDValue.cpp main.cpp)
set (HEADER_FILES common.hpp)

set_property (SOURCE main.cpp
              PROPERTY COMPILE_DEFINITIONS "CATCH_CONFIG_MAIN")

add_executable (test-UUIDValue ${SOURCE_FILES} ${HEADER_FILES})
    target_link_libraries (test-UUIDValue UUIDValue)
    target_include_directories (test-UUIDValue PRIVATE ${UUIDVALUE_SOURCE_DIR}/ext/Catch/single_include)
    target_compile_features (test-UUIDValue PRIVATE cxx_auto_type)

if (COMMAND cotire)
    cotire (test-UUIDValue)
endif ()

add_test (NAME test-UUIDValue
          COMMAND test-UUIDValue -r compact)
