//
// Created by Darwin Yuan on 2021/7/15.
//

#ifndef OBJECT_ARRAY_2_89AF5BBD02A3447D8624BECF1CB1B7FF
#define OBJECT_ARRAY_2_89AF5BBD02A3447D8624BECF1CB1B7FF

#include <l0-infra/array/concept/Less.h>

namespace mixin {
    template<typename T>
    struct ArrayRangeMinElem : T {
        using typename T::OffsetType;
        using typename T::SizeType;
        using typename T::ObjectType;
        using typename T::Maybe;
        using typename T::BitMap;

    public:
        template<__lEsS_cOnCePt(LESS)>
        auto RangeMinElemIndex(OffsetType from, OffsetType until, LESS &&less) const -> Maybe {
            return T::Unsafe_RangeMinElemIndex(T::OffsetToIndex(from), T::OffsetToIndex(until), std::forward<LESS>(less));
        }

        auto RangeMinElemIndex(OffsetType from, OffsetType until) const -> Maybe {
            return RangeMinElemIndex(from, until, T::GetLess());
        }

        template<__lEsS_cOnCePt(LESS)>
        auto MinElemIndexFrom(OffsetType from, LESS &&less) const -> Maybe {
            return T::Unsafe_RangeMinElemIndex(T::OffsetToIndex(from), T::IndexEnd(), std::forward<LESS>(less));
        }

        auto MinElemIndexFrom(OffsetType from) const -> Maybe {
            return MinElemIndexFrom(from, T::GetLess());
        }

        template<__lEsS_cOnCePt(LESS)>
        auto MinElemIndexUntil(OffsetType until, LESS &&less) const -> Maybe {
            return T::Unsafe_RangeMinElemIndex(T::IndexBegin(), T::OffsetToIndex(until), std::forward<LESS>(less));
        }

        auto MinElemIndexUntil(OffsetType until) const -> Maybe {
            return MinElemIndexUntil(until, T::GetLess());
        }

        template<__lEsS_cOnCePt(LESS)>
        auto RangeMinElemIndex(SizeType from, SizeType until, BitMap scope, LESS &&less) const -> Maybe {
            return T::Unsafe_RangeMinElemIndex(T::OffsetToIndex(from), T::OffsetToIndex(until), T::MaskScope(scope), std::forward<LESS>(less));
        }

        auto RangeMinElemIndex(SizeType from, SizeType until, BitMap scope) const -> Maybe {
            return RangeMinElemIndex(from, until, scope, T::GetLess());
        }

        template<__lEsS_cOnCePt(LESS)>
        auto MinElemIndexFrom(SizeType from, BitMap scope, LESS &&less) const -> Maybe {
            return T::Unsafe_RangeMinElemIndex(T::OffsetToIndex(from), T::IndexEnd(), T::MaskScope(scope), std::forward<LESS>(less));
        }

        auto MinElemIndexFrom(SizeType from, BitMap scope) const -> Maybe {
            return MinElemIndexFrom(from, scope, T::GetLess());
        }

        template<__lEsS_cOnCePt(LESS)>
        auto MinElemIndexUntil(SizeType until, BitMap scope, LESS &&less) const -> Maybe {
            return T::Unsafe_RangeMinElemIndex(T::IndexBegin(), T::OffsetToIndex(until), T::MaskScope(scope), std::forward<LESS>(less));
        }

        auto MinElemIndexUntil(SizeType until, BitMap scope) const -> Maybe {
            return MinElemIndexUntil(until, scope, T::GetLess());
        }

        template<__lEsS_cOnCePt(LESS)>
        auto RangeMinElemIndexEx(SizeType from, SizeType until, BitMap exclude, LESS &&less) const -> Maybe {
            return RangeMinElemIndex(from, until, ~exclude, std::forward<LESS>(less));
        }

        auto RangeMinElemIndexEx(SizeType from, SizeType until, BitMap exclude) const -> Maybe {
            return RangeMinElemIndexEx(from, until, exclude, T::GetLess());
        }

        template<__lEsS_cOnCePt(LESS)>
        auto MinElemIndexFromEx(SizeType from, BitMap exclude, LESS &&less) const -> Maybe {
            return MinElemIndexFrom(from, ~exclude, std::forward<LESS>(less));
        }

        auto MinElemIndexFromEx(SizeType from, BitMap exclude) const -> Maybe {
            return MinElemIndexFromEx(from, exclude, T::GetLess());
        }

        template<__lEsS_cOnCePt(LESS)>
        auto MinElemIndexUntilEx(SizeType until, BitMap exclude, LESS &&less) const -> Maybe {
            return MinElemIndexUntil(until, ~exclude, std::forward<LESS>(less));
        }

        auto MinElemIndexUntilEx(SizeType from, BitMap exclude) const -> Maybe {
            return MinElemIndexUntilEx(from, exclude, T::GetLess());
        }

        template<__lEsS_cOnCePt(LESS)>
        auto RangeMinElem(OffsetType from, OffsetType until, LESS &&less) const -> ObjectType const* {
            return T::Unsafe_RangeMinElem(T::OffsetToIndex(from), T::OffsetToIndex(until), std::forward<LESS>(less));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto MinElemFrom(OffsetType from, LESS &&less) const -> ObjectType const* {
            return T::Unsafe_RangeMinElem(T::OffsetToIndex(from), T::IndexEnd(), std::forward<LESS>(less));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto MinElemUntil(OffsetType until, LESS &&less) const -> ObjectType const* {
            return T::Unsafe_RangeMinElem(T::IndexBegin(), T::OffsetToIndex(until), std::forward<LESS>(less));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto RangeMinElem(SizeType from, SizeType until, BitMap scope, LESS &&less) const -> auto* {
            return T::Unsafe_RangeMinElem(T::OffsetToIndex(from), T::OffsetToIndex(until), T::MaskScope(scope), std::forward<LESS>(less));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto MinElemFrom(SizeType from, BitMap scope, LESS &&less) const -> auto* {
            return T::Unsafe_RangeMinElem(T::OffsetToIndex(from), T::IndexEnd(), T::MaskScope(scope), std::forward<LESS>(less));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto MinElemUntil(SizeType until, BitMap scope, LESS &&less) const -> auto* {
            return T::Unsafe_RangeMinElem(T::IndexBegin(), T::OffsetToIndex(until), T::MaskScope(scope), std::forward<LESS>(less));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto RangeMinElemEx(SizeType from, SizeType until, BitMap exclude, LESS &&less) const -> auto* {
            return RangeMinElem(from, until, ~exclude, std::forward<LESS>(less));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto MinElemFromEx(SizeType from, BitMap exclude, LESS &&less) const -> auto* {
            return MinElemFrom(from, ~exclude, std::forward<LESS>(less));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto MinElemUntilEx(SizeType until, BitMap exclude, LESS &&less) const -> auto* {
            return MinElemUntil(until, ~exclude, std::forward<LESS>(less));
        }
    };
}

#endif //OBJECT_ARRAY_2_89AF5BBD02A3447D8624BECF1CB1B7FF
