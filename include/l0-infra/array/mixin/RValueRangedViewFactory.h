//
// Created by Darwin Yuan on 2021/6/23.
//

#ifndef OBJECT_ARRAY_RVALUERANGEDVIEWFACTORY_H
#define OBJECT_ARRAY_RVALUERANGEDVIEWFACTORY_H

#include <l0-infra/array/mixin/ranged/RangedViewFactory.h>

namespace mixin {
    template<__cOnCePt(SimpleRangedArrayLike) T>
    struct RValueRangedViewFactory : RangedViewFactory<T> {
        using Self = RangedViewFactory<T>;
    public:
        using typename T::SizeType;
        using typename T::ObjectType;
        using typename T::OffsetType;

        using Self::IndexBegin;
        using Self::IndexEnd;

    public:
        using Self::Slice;
        using Self::From;
        using Self::Until;

        auto Slice(OffsetType from, OffsetType until) && -> auto {
            return Self::template MakeSlice<false, true>(from, until);
        }

        auto Slice(OffsetType from, OffsetType until) const && -> auto {
            return Self::template MakeSlice<true, true>(from, until);
        }

        auto From(OffsetType from) && -> auto {
            return std::move(*this).MakeFromSlice(from.ToIndex(IndexEnd()));
        }

        auto From(OffsetType from) const && -> auto {
            return std::move(*this).MakeFromSlice(from.ToIndex(IndexEnd()));
        }

        auto Until(OffsetType until) && -> auto {
            return std::move(*this).MakeUntilSlice(until.ToIndex(IndexEnd()));
        }

        auto Until(OffsetType until) const && -> auto {
            return std::move(*this).MakeUntilSlice(until.ToIndex(IndexEnd()));
        }
    };
}

#endif //OBJECT_ARRAY_RVALUERANGEDVIEWFACTORY_H
