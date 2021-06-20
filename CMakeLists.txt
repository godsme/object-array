cmake_minimum_required(VERSION 3.19)
project(object_array)

set(CMAKE_CXX_STANDARD 20)

include_directories(
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/third-party"
)

add_executable(object_array_test test/ut/catch.cpp third-party/boost/ut.hpp include/object-array/concept/SimpleFind.h include/object-array/concept/Pred.h include/object-array/mixin/UnscopedSimpleFind.h include/object-array/concept/RangedArrayLike.h test/ut/UnscopedSimpleFindTest.cpp include/object-array/detail/MixinDef.h)