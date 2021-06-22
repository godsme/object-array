//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_RANGEDVIEWFACTORY_H
#define OBJECT_ARRAY_RANGEDVIEWFACTORY_H

#include <object-array/mixin/detail/DefMixin.h>
#include <object-array/concept/IndexedContainer.h>
#include <object-array/view/Slice.h>

namespace mixin {
    __Def_Mixin(RangedViewFactory, _concept::IndexedContainer) {
    public:
        using SizeType = typename T::SizeType;
        using ObjectType = typename T::ObjectType;
        using IndexedContainer = typename T::IndexedContainer;
        using DataHolder = typename T::DataHolder;

        auto Slice(SizeType from, SizeType to) && -> auto {
            struct Array : private DataHolder, IndexedContainer {
                using DataHolder::DataHolder;
                using IndexedContainer::GetObj;
                using SizeType = typename DataHolder::SizeType;
                using ObjectType = typename DataHolder::ObjectType;
                using ElemType = typename DataHolder::ElemType;
                Array(Array&&) = default;
            };

            return view::ValueSlice<Array>{reinterpret_cast<Array&&>(*this), from, to};
        }
    };
}

#endif //OBJECT_ARRAY_RANGEDVIEWFACTORY_H
