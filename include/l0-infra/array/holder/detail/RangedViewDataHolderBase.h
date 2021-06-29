//
// Created by Darwin Yuan on 2021/6/28.
//

#ifndef OBJECT_ARRAY_RANGEDVIEWDATAHOLDERBASE_H
#define OBJECT_ARRAY_RANGEDVIEWDATAHOLDERBASE_H

#include <l0-infra/array/concept/RangedArrayLike.h>
#include <l0-infra/array/holder/detail/DeduceElemType.h>
#include <l0-infra/array/holder/detail/ObjectTrait.h>
#include <l0-infra/array/holder/detail/RangedViewDataHolderInterface.h>
#include <l0-infra/array/holder/detail/ArrayLikeViewDataHolder.h>
#include <l0-infra/array/holder/detail/ViewDataHolder.h>
#include <l0-infra/base/BitSet.h>

namespace holder::detail {
    template<__cOnCePt(SimpleRangedArrayLike) ARRAY, typename SUB_TYPE, bool ORDERED>
    struct RangedViewDataHolderBase : ViewDataHolder<ARRAY> {
        using Parent = ViewDataHolder<ARRAY>;
        using typename Parent::SizeType;
        using typename Parent::ObjectType;
        constexpr static bool IS_ORDERED = ORDERED;

    protected:
        dEcL_tHiS(SUB_TYPE);

    protected:
        auto GetObj(SizeType n) const -> ObjectType const& {
            return This()->GetArray().GetObj(n);
        }

        auto GetObj(SizeType n) -> ObjectType& {
            return This()->GetArray().GetObj(n);
        }
    };
}

#endif //OBJECT_ARRAY_RANGEDVIEWDATAHOLDERBASE_H
