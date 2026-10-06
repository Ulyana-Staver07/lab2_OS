cmake_minimum_required(VERSION 3.15)
project(Lab02_CMake CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(ArrayUtils SHARED
    ArrayUtils.h
    ArrayUtils.cpp
)
target_compile_definitions(ArrayUtils PRIVATE ARRAYUTILS_EXPORTS)

add_executable(Lab02_CMake
    main.cpp
)

add_dependencies(Lab02_CMake ArrayUtils)

add_custom_command(TARGET Lab02_CMake POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:ArrayUtils>
        $<TARGET_FILE_DIR:Lab02_CMake>
)