//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_SCOPEDVIEWFACTORY_H
#define OBJECT_ARRAY_SCOPEDVIEWFACTORY_H

#include <object-array/concept/ScopedArrayLike.h>
#include <object-array/view/ScopedView.h>

namespace mixin {
    template<_concept::SimpleRangedArrayLike T>
    struct ScopedViewFactory : T {
        using Self = T;
    public:
        using SizeType = typename T::SizeType;
        using ObjectType = typename T::ObjectType;
        using BitMap = typename T::BitMap;
        using RangedArrayLike = typename T::RangedArrayLike;

        using Self::IndexBegin;
        using Self::IndexEnd;

    protected:
        auto AlignScope(BitMap scope) const -> BitMap {
            return scope.Align(IndexBegin(), IndexEnd());
        }

    public:
        auto Scope(BitMap scope) && -> void {}
        auto Scope(BitMap scope) const && -> void {}

        auto Scope(BitMap scope) & -> view::ScopedView<RangedArrayLike> {
            return {static_cast<RangedArrayLike&>(*this), AlignScope(scope)};
        }

        auto Scope(BitMap scope) const & -> view::ScopedView<RangedArrayLike const> {
            return {static_cast<RangedArrayLike const&>(*this), AlignScope(scope)};
        }

        auto Exclude(BitMap excluded) && -> void {}
        auto Exclude(BitMap excluded) const && -> void {}

        auto Exclude(BitMap excluded) & -> auto {
            return Scope(~excluded);
        }

        auto Exclude(BitMap excluded) const & -> auto {
            return Scope(~excluded);
        }
    };
}

#endif //OBJECT_ARRAY_SCOPEDVIEWFACTORY_H
