//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_MIXIN_INDEXEDCONTAINER_H
#define OBJECT_ARRAY_MIXIN_INDEXEDCONTAINER_H

#include <l0-infra/array/detail/ConceptDef.h>
#include <l0-infra/array/concept/ArrayLike.h>

namespace mixin {
    template<__cOnCePt(ConstArrayLike) T>
    class IndexedContainer : public T {
        using Self = T;

    public:
        using typename T::SizeType;
        using typename T::ObjectType;

    protected:
        using IndexContainer = IndexedContainer;

    public:
        auto GetObj(SizeType n) const -> ObjectType const& { return T::ConstElemToObject(Self::Elems()[n]); }
        auto GetObj(SizeType n) -> ObjectType& { return T::ElemToObject(Self::Elems()[n]); }
    };
}

#endif //OBJECT_ARRAY_MIXIN_INDEXEDCONTAINER_H
