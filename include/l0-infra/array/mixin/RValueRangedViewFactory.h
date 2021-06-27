//
// Created by Darwin Yuan on 2021/6/23.
//

#ifndef OBJECT_ARRAY_RVALUERANGEDVIEWFACTORY_H
#define OBJECT_ARRAY_RVALUERANGEDVIEWFACTORY_H

#include <l0-infra/array/mixin/RangedViewFactory.h>

namespace mixin {
    template<__cOnCePt(SimpleRangedArrayLike) T>
    struct RValueRangedViewFactory : RangedViewFactory<T> {
        using Self = RangedViewFactory<T>;
    public:
        using typename T::SizeType;
        using typename T::ObjectType;
        using typename T::OffsetType;
        using typename T::EndOffsetType;

        using Self::IndexBegin;
        using Self::IndexEnd;

    public:
        using Self::Slice;
        using Self::From;
        using Self::Until;

        auto Slice(OffsetType from, EndOffsetType until) && -> auto {
            return Self::template MakeSlice<false, true>(from, until);
        }

        auto Slice(OffsetType from, EndOffsetType until) const && -> auto {
            return Self::template MakeSlice<true, true>(from, until);
        }

        auto From(OffsetType from) && -> auto {
            return std::move(*this).MakeSlice(from.ToIndex(IndexEnd()), IndexEnd());
        }

        auto From(OffsetType from) const && -> auto {
            return std::move(*this).MakeSlice(from.ToIndex(IndexEnd()), IndexEnd());
        }

        auto Until(EndOffsetType until) && -> auto {
            return std::move(*this).MakeSlice(IndexBegin(), until.ToIndex(IndexEnd()));
        }

        auto Until(EndOffsetType until) const && -> auto {
            return std::move(*this).MakeSlice(IndexBegin(), until.ToIndex(IndexEnd()));
        }
    };
}

#endif //OBJECT_ARRAY_RVALUERANGEDVIEWFACTORY_H