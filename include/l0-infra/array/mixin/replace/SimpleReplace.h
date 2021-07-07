//
// Created by Darwin Yuan on 2021/7/3.
//

#ifndef OBJECT_ARRAY_SIMPLEREPLACE_H
#define OBJECT_ARRAY_SIMPLEREPLACE_H

#include <l0-infra/array/detail/ConceptDef.h>
#include <l0-infra/array/concept/ContiguousArrayLikeDataHolder.h>
#include <l0-infra/array/mixin/erase/SimpleDoErase.h>

namespace mixin {
    template<typename T>
    class SimpleReplace : public T {
        using Self = T;

    public:
        using typename T::OffsetType;
        using typename T::ObjectType;

    public:
        template<typename ... ARGS>
        auto Replace(OffsetType i, ARGS &&... args) -> ObjectType * {
            return Self::DoReplace(i.ToIndex(Self::IndexEnd() - Self::IndexBegin()), std::forward<ARGS>(args)...);
        }
    };
}

#endif //OBJECT_ARRAY_SIMPLEREPLACE_H
