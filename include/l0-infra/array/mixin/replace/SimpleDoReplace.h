//
// Created by Darwin Yuan on 2021/7/3.
//

#ifndef OBJECT_ARRAY_SIMPLEDOREPLACE_H
#define OBJECT_ARRAY_SIMPLEDOREPLACE_H

#include <l0-infra/array/detail/ConceptDef.h>
#include <l0-infra/array/concept/ContiguousArrayLikeDataHolder.h>
#include <l0-infra/array/mixin/erase/SimpleDoErase.h>

namespace mixin {
    template<__cOnCePt(ContiguousArrayLikeDataHolder) T>
    class SimpleDoReplace : public T {
        using Self = T;

    public:
        using typename T::SizeType;
        using typename T::ObjectType;

    protected:
        using Self::Elems;

    public:
        template<typename ... ARGS>
        auto DoReplace(SizeType i, ARGS&& ... args) -> ObjectType* {
            return Self::Trait::Replace(Elems()[i], std::forward<ARGS>(args)...);
        }
    };
}

#endif //OBJECT_ARRAY_SIMPLEDOREPLACE_H
