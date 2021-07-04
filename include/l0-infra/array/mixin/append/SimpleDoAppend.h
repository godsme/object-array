//
// Created by Darwin Yuan on 2021/7/4.
//

#ifndef OBJECT_ARRAY_SIMPLEDOAPPEND_H
#define OBJECT_ARRAY_SIMPLEDOAPPEND_H

#include <l0-infra/array/detail/ConceptDef.h>
#include <l0-infra/array/concept/ContiguousArrayLikeDataHolder.h>
#include <l0-infra/array/mixin/erase/SimpleDoErase.h>

namespace mixin {
    template<__cOnCePt(ContiguousArrayLikeDataHolder) T>
    class SimpleDoAppend : public T {
        using Self = T;

    public:
        using typename T::SizeType;
        using typename T::ObjectType;

        static constexpr auto MAX_SIZE = T::MAX_SIZE;

    protected:
        using Self::Num;
        using Self::Elems;

        using typename Self::Trait;

    public:
        template<typename ... ARGS>
        auto DoAppend(ARGS &&... args) -> ObjectType * {
            return Num() < MAX_SIZE ? Trait::Emplace(Elems()[Num()++], std::forward<ARGS>(args)...) : nullptr;
        }
    };
}

#endif //OBJECT_ARRAY_SIMPLEDOAPPEND_H
