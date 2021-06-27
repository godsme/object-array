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
#include <l0-infra/base/BitSet.h>

namespace holder::detail {
    template<__cOnCePt(SimpleRangedArrayLike) ARRAY, typename OWNER, typename SUB_TYPE>
    struct RangedViewDataHolderBase {
        constexpr static auto IsConstArray = std::is_const_v<ARRAY>;
        using ArrayType = std::decay_t<ARRAY>;

        using ObjectType = std::conditional_t<IsConstArray, std::add_const_t<typename ArrayType::ObjectType>, typename ArrayType::ObjectType>;
        using SizeType   = typename ArrayType::SizeType;
        using Owner = OWNER;

        constexpr static SizeType MAX_SIZE = ArrayType::MAX_SIZE;

    protected:
        dEcL_tHiS(SUB_TYPE);

    public:
        auto GetObj(SizeType n) const -> ObjectType const& {
            return This()->GetArray().GetObj(n);
        }

        auto GetObj(SizeType n) -> ObjectType& {
            return This()->GetArray().GetObj(n);
        }
    };
}

#endif //OBJECT_ARRAY_RANGEDVIEWDATAHOLDERBASE_H
