//
// Created by Darwin Yuan on 2021/7/12.
//

#ifndef OBJECT_ARRAY_2_2BF58F07E88248B69B0FF3A4F2E8CA44
#define OBJECT_ARRAY_2_2BF58F07E88248B69B0FF3A4F2E8CA44

#include <l0-infra/array/concept/Pred.h>

namespace mixin {
    template<typename T>
    struct UnsafeSliceScopedFind : T {
        using typename T::SizeType;
        using typename T::ObjectType;
        using typename T::BitMap;
        using typename T::Maybe;

    public:
        template<__pRed_CoNcEpT(PRED)>
        auto Unsafe_ScopeFindIndex(BitMap scope, PRED&& pred) const -> Maybe {
            return T::GetArray().Unsafe_RangeScopeFindIndex(T::IndexBegin(), T::IndexEnd(), scope, std::forward<PRED>(pred));
        }

        template<__pRed_CoNcEpT(PRED)>
        auto Unsafe_ScopeFind(BitMap scope, PRED&& pred) const -> ObjectType const* {
            return T::GetArray().Unsafe_RangeScopeFind(T::IndexBegin(), T::IndexEnd(), scope, std::forward<PRED>(pred));
        }
    };
}

#endif //OBJECT_ARRAY_2_2BF58F07E88248B69B0FF3A4F2E8CA44
