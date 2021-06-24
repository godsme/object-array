//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_RANGEDVIEWFACTORY_H
#define OBJECT_ARRAY_RANGEDVIEWFACTORY_H

#include <object-array/concept/RangedArrayLike.h>
#include <object-array/view/Slice.h>

namespace mixin {
    template<_concept::SimpleRangedArrayLike T>
    struct RangedViewFactory : T {
        using Self = T;
    public:
        using SizeType = typename T::SizeType;
        using ObjectType = typename T::ObjectType;
        using OffsetType = typename T::OffsetType;
        using EndOffsetType = typename T::EndOffsetType;
        using IndexedContainer = typename T::IndexedContainer;

        using Self::IndexBegin;
        using Self::IndexEnd;

    private:
        auto MakeSlice(SizeType from, SizeType until) & -> view::Slice<IndexedContainer> {
            return {static_cast<IndexedContainer&>(*this), from, until};
        }

        auto MakeSlice(SizeType from, SizeType until) const & -> view::Slice<IndexedContainer const> {
            return {static_cast<IndexedContainer const&>(*this), from, until};
        }

    public:
        auto Slice(OffsetType, EndOffsetType) && -> void {}
        auto Slice(OffsetType, EndOffsetType) const && -> void {}

        auto Slice(OffsetType from, EndOffsetType until) & -> auto {
            return MakeSlice(from.ToIndex(IndexEnd()), until.ToIndex(IndexEnd()));
        }

        auto Slice(OffsetType from, EndOffsetType until) const & -> auto {
            return MakeSlice(from.ToIndex(IndexEnd()), until.ToIndex(IndexEnd()));
        }

        auto From(OffsetType) && -> void {}
        auto From(OffsetType) const && -> void {}

        auto From(OffsetType from) & -> auto {
            return MakeSlice(from.ToIndex(IndexEnd()), IndexEnd());
        }

        auto From(OffsetType from) const& -> auto {
            return MakeSlice(from.ToIndex(IndexEnd()), IndexEnd());
        }

        auto Until(EndOffsetType) && -> void {}
        auto Until(EndOffsetType) const && -> void {}

        auto Until(EndOffsetType until) & -> auto {
            return MakeSlice(IndexBegin(), until.ToIndex(IndexEnd()));
        }

        auto Until(EndOffsetType until) const& -> auto {
            return MakeSlice(IndexBegin(), until.ToIndex(IndexEnd()));
        }
    };
}

#endif //OBJECT_ARRAY_RANGEDVIEWFACTORY_H
