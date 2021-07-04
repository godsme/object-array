//
// Created by Darwin Yuan on 2021/6/23.
//

#ifndef OBJECT_ARRAY_RVALUESCOPEDVIEWFACTORY_H
#define OBJECT_ARRAY_RVALUESCOPEDVIEWFACTORY_H

#include <l0-infra/array/mixin/factory/ScopedViewFactory.h>
#include <l0-infra/array/mixin/detail/ValueRangedArray.h>

namespace mixin {
    template<__cOnCePt(SimpleRangedArrayLike) T>
    struct RValueScopedViewFactory : ScopedViewFactory<T> {
        using Self = ScopedViewFactory<T>;

    public:
        using typename T::SizeType;
        using typename T::ObjectType;
        using typename T::BitMap;

    protected:
        using typename T::RangedArrayLike;
        using typename T::DataHolder;
        using Self::ORDERED;

    private:
        using Array = detail::ValueRangedArray<DataHolder, RangedArrayLike>;

    public:
        using Self::Scope;
        using Self::Exclude;

        auto Scope(BitMap scope) && -> view::ValueScopedView<Array, ORDERED> {
            return {reinterpret_cast<Array&&>(*this), Self::MaskScope(scope)};
        }

        auto Scope(BitMap scope) const && -> view::ValueScopedView<Array const, ORDERED> {
            return {reinterpret_cast<Array const&&>(*this), Self::MaskScope(scope)};
        }

        auto Exclude(BitMap excluded) && -> auto {
            return std::move(*this).Scope(~excluded);
        }

        auto Exclude(BitMap excluded) const && -> auto {
            return std::move(*this).Scope(~excluded);
        }
    };
}

#endif //OBJECT_ARRAY_RVALUESCOPEDVIEWFACTORY_H
