//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_MIXIN_INDEXEDCONTAINER_H
#define OBJECT_ARRAY_MIXIN_INDEXEDCONTAINER_H

#include <object-array/concept/ArrayLike.h>

namespace mixin {
    template<_concept::ConstArrayLike T>
    struct IndexedContainer : T {
        using Self = T;
    public:
        using typename T::SizeType;
        using typename T::ObjectType;
        using IndexContainer = IndexedContainer;

        auto GetObj(SizeType n) const -> ObjectType const& { return T::ElemToObject(Self::Elems()[n]); }
        auto GetObj(SizeType n) -> ObjectType& { return T::ElemToObject(Self::Elems()[n]); }
    };
}

#endif //OBJECT_ARRAY_MIXIN_INDEXEDCONTAINER_H
