//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_SCOPEDVIEWFACTORY_H
#define OBJECT_ARRAY_SCOPEDVIEWFACTORY_H

#include <l0-infra/array/concept/ScopedArrayLike.h>
#include <l0-infra/array/view/ScopedView.h>

namespace mixin {
    template<__cOnCePt(SimpleRangedArrayLike) T>
    struct ScopedViewFactory : T {
        using Self = T;

    public:
        using typename T::SizeType;
        using typename T::ObjectType;
        using typename T::BitMap;

    protected:
        using typename T::RangedArrayLike;
        using Self::IndexBegin;
        using Self::IndexEnd;

    protected:
        auto MaskScope(BitMap scope) const -> BitMap {
            return scope.Mask(IndexBegin(), IndexEnd());
        }

    public:
        auto Scope(BitMap scope) && -> void {}
        auto Scope(BitMap scope) const && -> void {}

        auto Scope(BitMap scope) & -> view::ScopedView<RangedArrayLike> {
            return {static_cast<RangedArrayLike&>(*this), MaskScope(scope)};
        }

        auto Scope(BitMap scope) const & -> view::ScopedView<RangedArrayLike const> {
            return {static_cast<RangedArrayLike const&>(*this), MaskScope(scope)};
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
