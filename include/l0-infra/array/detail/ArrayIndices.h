//
// Created by Darwin Yuan on 2021/7/10.
//

#ifndef OBJECT_ARRAY_2_ACD2C08371514BCDA190EA6AE571EDBE
#define OBJECT_ARRAY_2_ACD2C08371514BCDA190EA6AE571EDBE

#include <l0-infra/array/holder/ObjectArrayHolder.h>
#include <l0-infra/array/mixin/detail/Mixins.h>
#include <l0-infra/array/mixin/array_like/ConstArrayLike.h>
#include <l0-infra/array/mixin/detail/___mutable_mixin_delimiter___.h>
#include <l0-infra/array/mixin/array_like/ArrayLike.h>
#include <l0-infra/array/mixin/array_like/ContiguousArrayLike.h>
#include <l0-infra/array/mixin/erase/SimpleErase.h>
#include <l0-infra/array/mixin/append/SimpleAppend.h>
#include <l0-infra/array/mixin/sort/ContiguousRangeSort.h>
#include <l0-infra/array/mixin/access/ByIndexRefAccessor.h>
#include <l0-infra/array/mixin/access/ByIndexAccessor.h>
#include <l0-infra/array/mixin/count/RangedElemCount.h>
#include <l0-infra/array/mixin/append/AppendExporter.h>
#include <l0-infra/array/mixin/array_like/ContiguousArrayRange.h>
#include <l0-infra/array/mixin/index/ObjectIndex.h>
#include <l0-infra/array/mixin/foreach/ArrayElemVisit.h>
#include <l0-infra/array/mixin/foreach/SimpleRangeForEach.h>
#include <l0-infra/array/mixin/min/ContiguousRangeMinElem.h>
#include <l0-infra/array/mixin/find/UnsafeRangeFind.h>
#include <l0-infra/array/mixin/foreach/UnsafeRangeScopeForEach.h>
#include <l0-infra/array/mixin/find/UnsafeScopedRangeFind.h>
#include <l0-infra/array/mixin/min/UnsafeRangeScopeMinElem.h>
#include <l0-infra/array/mixin/find/NonScopedSimpleFind.h>
#include <l0-infra/array/mixin/find/SimpleFindExt.h>
#include <l0-infra/array/mixin/find/UnsafeScopedFind.h>
#include <l0-infra/array/mixin/find/ScopeFindExt.h>
#include <l0-infra/array/mixin/foreach/SimpleForEach.h>
#include <l0-infra/array/mixin/foreach/SimpleForEachExt.h>
#include <l0-infra/array/mixin/foreach/ArrayScopedForEach.h>
#include <l0-infra/array/mixin/foreach/ScopedForEachExt.h>
#include <l0-infra/array/mixin/min/SimpleMinElem.h>
#include <l0-infra/array/mixin/min/ScopedMinElemExt.h>
#include <l0-infra/array/mixin/min/SimpleMinElemExt.h>
#include <l0-infra/array/mixin/erase/RangedClear.h>
#include <l0-infra/array/mixin/erase/ClearExt.h>
#include <l0-infra/array/mixin/foreach/UnsafeRangeForEach.h>
#include <l0-infra/array/mixin/access/RangeExporter.h>
#include <l0-infra/array/mixin/iterable/IterableArrayLike.h>

namespace array_indices {
    using Private = ::mixin::Private<
            mixin::ContiguousArrayLike,
            mixin::ConstArrayLike,
            mixin::ContiguousArrayRange,
            mixin::ObjectIndex,
            mixin::ArrayElemVisit,
            mixin::SimpleRangeForEach,
            mixin::ContiguousRangeMinElem,
            mixin::UnsafeRangeScopeForEach,
            mixin::UnsafeScopedRangeFind,
            mixin::UnsafeRangeScopeMinElem,
            mixin::UnsafeScopedFind,
            mixin::SimpleForEach,
            mixin::ArrayScopedForEach,
            mixin::___mutable_mixin_delimiter___,
            mixin::ArrayLike,
            mixin::SimpleErase,
            mixin::SimpleAppend,
            mixin::RangedClear>;

    using Public = ::mixin::Public<
            mixin::RangeExporter,
            mixin::ByIndexRefAccessor,
            mixin::ByIndexAccessor,
            mixin::RangedElemCount,
            mixin::IterableArrayLike,
            mixin::UnsafeRangeFind,
            mixin::NonScopedSimpleFind,
            mixin::SimpleFindExt,
            mixin::ScopeFindExt,
            mixin::UnsafeRangeForEach,
            mixin::SimpleForEachExt,
            mixin::ScopedForEachExt,
            mixin::SimpleMinElem,
            mixin::SimpleMinElemExt,
            mixin::ScopedMinElemExt,
            mixin::___mutable_mixin_delimiter___,
            mixin::ContiguousRangeSort,
            mixin::AppendExporter,
            mixin::ClearExt>;

    template<std::size_t MAX_NUM>
    struct Array : Public::Compose<holder::ObjectArrayHolder<::detail::DeduceIntOptSizeType_t<MAX_NUM>, MAX_NUM>, Private, Array<MAX_NUM>> {
        using Parent = Public::Compose<holder::ObjectArrayHolder<::detail::DeduceIntOptSizeType_t<MAX_NUM>, MAX_NUM>, Private, Array<MAX_NUM>>;
        using Parent::Parent;
        using typename Parent::SizeType;

        Array() {}

        template<typename ARRAY>
        Array(Array const& array) {
            Init(array);
        }

        template<typename BITMAP>
        Array(SizeType from, SizeType until, BITMAP scope) {
            Init(from, until, scope);
        }

        template<typename ARRAY>
        Array(Array const& array, typename ARRAY::BitMap scope) {
            Init(array, scope);
        }

        template<typename ARRAY>
        auto Init(ARRAY const& array) -> void {
            Parent::Clear();
            for(auto i = array.IndexBegin(); i < array.IndexEnd(); ++i) {
                Parent::Append(i);
            }
        }

        template<typename ARRAY>
        auto Init(ARRAY const& array, typename ARRAY::BitMap scope) {
            Parent::Clear();
            for(auto i = array.IndexBegin(); i < array.IndexEnd(); ++i) {
                if(scope[i]) Parent::Append(i);
            }
        }

        template<typename BITMAP>
        auto Init(SizeType from, SizeType until, BITMAP scope) {
            Parent::Clear();
            for(auto i = from; i < until; ++i) {
                if(scope[i]) Parent::Append(i);
            }
        }
    };
}

#endif //OBJECT_ARRAY_2_ACD2C08371514BCDA190EA6AE571EDBE
