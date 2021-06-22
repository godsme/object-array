cmake_minimum_required(VERSION 3.19)
project(object_array)

#set(CMAKE_CXX_COMPILER "g++-10")

set(CMAKE_CXX_STANDARD 20)

include_directories(
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/third-party"
)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -frelaxed-template-template-args")
endif()

add_executable(object_array_test test/ut/catch.cpp third-party/boost/ut.hpp include/object-array/concept/SimpleFind.h include/object-array/concept/Pred.h include/object-array/mixin/NonScopedSimpleFind.h include/object-array/concept/RangedArrayLike.h test/ut/UnscopedSimpleFindTest.cpp include/object-array/mixin/SimpleFindExt.h include/cub/base/InvokeConstMethod.h include/object-array/mixin/RangedArrayLike.h include/object-array/holder/ScatteredArrayDataHolder.h include/cub/base/Placement.h include/cub/base/detail/StorageTrait.h include/cub/base/DeduceSizeType.h include/cub/base/DeduceOffsetType.h include/object-array/holder/detail/DeduceElemType.h include/object-array/holder/ArrayDataHolder.h include/object-array/holder/ObjectArrayDataHolder.h include/cub/base/IntBitSet.h include/cub/base/detail/DeduceBitSetIntType.h include/cub/base/BitSet.h include/object-array/holder/detail/ObjectTrait.h test/ut/ObjectArrayDataHolderTest.cpp test/ut/ScatteredArrayDataHolderTest.cpp include/object-array/concept/ArrayLike.h include/object-array/mixin/RangedArray.h include/object-array/holder/ScatteredArrayHolder.h test/ut/ScatteredArrayHolderTest.cpp include/object-array/mixin/detail/Combinator.h include/object-array/mixin/ContinuousArrayLike.h include/object-array/concept/ContinuousArrayLikeDataHolder.h include/object-array/concept/SimpleArrayLike.h include/object-array/holder/ObjectArrayHolder.h test/ut/ObjectArrayHolderTest.cpp include/object-array/mixin/detail/Public.h include/object-array/mixin/ScopedSimpleFind.h include/object-array/concept/ScopedArrayLike.h include/object-array/mixin/ScopedFind.h test/ut/ScopedSimpleFindTest.cpp include/object-array/mixin/ScopedRangedArrayLike.h)