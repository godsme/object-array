//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_SCOPEDVIEWFACTORY_H
#define OBJECT_ARRAY_SCOPEDVIEWFACTORY_H

#include <object-array/mixin/detail/DefMixin.h>
#include <object-array/concept/ScopedArrayLike.h>
#include <object-array/view/ScopedView.h>

namespace mixin {
    __Def_Mixin(ScopedViewFactory, _concept::SimpleRangedArrayLike) {
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

            using SizeType = typename DataHolder::SizeType;
            using ObjectType = typename DataHolder::ObjectType;
            using ElemType = typename DataHolder::ElemType;

            constexpr static auto MAX_SIZE = DataHolder::MAX_SIZE;
            Array(Array&&) = default;
        };

    public:
        auto Scope(BitMap scope) && -> auto {
            return view::ValueScopedView<Array>{reinterpret_cast<Array&&>(*this), scope};
        }

        auto Scope(BitMap scope) & -> auto {
            return view::ScopedView<RangedArrayLike>{static_cast<RangedArrayLike&>(*this), scope};
        }

        auto Exclude(BitMap excluded) && -> auto {
            return std::move(*this).Scope(~excluded);
        }

        auto Exclude(BitMap excluded) & -> auto {
            return Scope(~excluded);
        }
    };
}

#endif //OBJECT_ARRAY_SCOPEDVIEWFACTORY_H
