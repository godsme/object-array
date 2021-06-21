cmake_minimum_required(VERSION 3.19)
project(object_array)

set(CMAKE_CXX_STANDARD 20)

include_directories(
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/third-party"
)

add_executable(object_array_test test/ut/catch.cpp third-party/boost/ut.hpp include/object-array/concept/SimpleFind.h include/object-array/concept/Pred.h include/object-array/mixin/UnscopedSimpleFind.h include/object-array/concept/RangedArrayLike.h test/ut/UnscopedSimpleFindTest.cpp include/object-array/detail/MixinDef.h include/object-array/mixin/SimpleFindExt.h test/ut/SimpleFindExtTest.cpp include/cub/base/InvokeConstMethod.h include/object-array/mixin/RangedArrayLike.h include/object-array/holder/ScatteredArrayDataHolder.h include/cub/base/Placement.h include/cub/base/detail/StorageTrait.h include/cub/base/DeduceSizeType.h include/cub/base/DeduceOffsetType.h include/object-array/holder/detail/DeduceElemType.h include/object-array/holder/ArrayDataHolder.h include/object-array/holder/ObjectArrayDataHolder.h include/cub/base/IntBitSet.h include/cub/base/detail/DeduceBitSetIntType.h include/cub/base/BitSet.h include/object-array/holder/detail/ObjectTrait.h test/ut/ObjectArrayDataHolderTest.cpp)