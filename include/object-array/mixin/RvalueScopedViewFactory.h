//
// Created by Darwin Yuan on 2021/6/23.
//

#ifndef OBJECT_ARRAY_RVALUESCOPEDVIEWFACTORY_H
#define OBJECT_ARRAY_RVALUESCOPEDVIEWFACTORY_H

#include <object-array/mixin/ScopedViewFactory.h>

namespace mixin {
    template<_concept::SimpleRangedArrayLike T>
    struct RValueScopedViewFactory : detail::Extends<ScopedViewFactory<T>> {
        using Self = detail::Extends<ScopedViewFactory<T>>;
    public:
        using SizeType = typename T::SizeType;
        using ObjectType = typename T::ObjectType;
        using BitMap = typename T::BitMap;
        using RangedArrayLike = typename T::RangedArrayLike;
        using DataHolder = typename T::DataHolder;

    private:
        struct Array : private DataHolder, RangedArrayLike {
            using DataHolder::DataHolder;
            using RangedArrayLike::GetObj;
            using RangedArrayLike::IndexBegin;
            using RangedArrayLike::IndexEnd;

            using BitMap = BitMap;
            using SizeType = typename DataHolder::SizeType;
            using ObjectType = typename DataHolder::ObjectType;
            using ElemType = typename DataHolder::ElemType;

            constexpr static auto MAX_SIZE = DataHolder::MAX_SIZE;
            Array(Array&&) = default;
        };

    public:
        using Self::Scope;
        using Self::Exclude;

        auto Scope(BitMap scope) && -> view::ValueScopedView<Array> {
            return {reinterpret_cast<Array&&>(*this), scope};
        }

        auto Scope(BitMap scope) const && -> view::ValueScopedView<Array const> {
            return {reinterpret_cast<Array const&&>(*this), scope};
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
