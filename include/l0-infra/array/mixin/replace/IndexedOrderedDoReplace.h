//
// Created by Darwin Yuan on 2021/7/3.
//

#ifndef OBJECT_ARRAY_INDEXEDORDEREDDOREPLACE_H
#define OBJECT_ARRAY_INDEXEDORDEREDDOREPLACE_H

#include <l0-infra/array/detail/ConceptDef.h>
#include <l0-infra/array/concept/ContiguousArrayLikeDataHolder.h>
#include <l0-infra/array/mixin/erase/SimpleDoErase.h>

namespace mixin {
    template<typename T>
    class IndexedOrderedDoReplace : public T {
        using Self = T;

    public:
        using typename T::SizeType;
        using typename T::ObjectType;

    protected:
        using Self::Elems;
        using Self::GetIndices;

    public:
        template<typename ... ARGS>
        auto DoReplace(SizeType i, ARGS&& ... args) -> ObjectType* {
            auto index = GetIndices()[i];
            auto* p = Self::Replace(index, std::forward<ARGS>(args)...);
            GetIndices().ActualReplace(Self::GetIndicesLess(), i, index);
            return p;
        }
    };
}

#endif //OBJECT_ARRAY_INDEXEDORDEREDDOREPLACE_H
