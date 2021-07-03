//
// Created by Darwin Yuan on 2021/6/24.
//

#ifndef OBJECT_ARRAY_SIMPLEAPPEND_H
#define OBJECT_ARRAY_SIMPLEAPPEND_H

#include <l0-infra/array/detail/ConceptDef.h>
#include <l0-infra/array/concept/ContiguousArrayLikeDataHolder.h>
#include <l0-infra/array/mixin/erase/SimpleDoErase.h>

namespace mixin {
    template<__cOnCePt(ContiguousArrayLikeDataHolder) T>
    class SimpleAppend : public T {
        using Self = T;

    public:
        using typename T::SizeType;
        using typename T::ObjectType;

        static constexpr auto MAX_SIZE = T::MAX_SIZE;

    protected:
        using Self::GetObj;
        using Self::Num;
        using Self::Elems;

        using typename Self::Trait;

    public:
        template<typename ... ARGS>
        auto Append(ARGS &&... args) -> ObjectType * {
            return Num() < MAX_SIZE ? Trait::Emplace(Elems()[Num()++], std::forward<ARGS>(args)...) : nullptr;
        }
    };
}

#endif //OBJECT_ARRAY_SIMPLEAPPEND_H
