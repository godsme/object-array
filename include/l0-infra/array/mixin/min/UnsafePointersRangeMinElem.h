//
// Created by Darwin Yuan on 2021/7/13.
//

#ifndef OBJECT_ARRAY_2_177C7B5F302B40018BA31493EC02D539
#define OBJECT_ARRAY_2_177C7B5F302B40018BA31493EC02D539

#include <l0-infra/array/concept/Less.h>

namespace mixin {
    template<typename T>
    struct UnsafePointerRangeMinElem : T {
        using typename T::SizeType;
        using typename T::ObjectType;
        using typename T::Maybe;

    protected:
        template<__lEsS_cOnCePt(LESS)>
        auto GetPointerLess(LESS&& less) -> auto {
            return [&](auto* l, auto* r) -> bool { return less(*l, *r); };
        }

    public:
        template<__lEsS_cOnCePt(LESS)>
        auto Unsafe_RangeMinElemIndex(SizeType from, SizeType until, LESS &&less) const -> Maybe {
            return T::GetPointers().Unsafe_RangeMinElemIndex(from, until, GetPointerLess(std::forward<LESS>(less)));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto Unsafe_RangeMinElem(SizeType from, SizeType until, LESS &&less) const -> ObjectType const* {
            auto* p = T::GetPointers().Unsafe_RangeMinElem(from, until, GetPointerLess(std::forward<LESS>(less)));
            return p == nullptr ? nullptr : *p;
        }
    };
}

#endif //OBJECT_ARRAY_2_177C7B5F302B40018BA31493EC02D539
