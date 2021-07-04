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
        template<typename ... ARGS>
        auto Append(ARGS &&... args) -> typename T::ObjectType * {
            return Self::DoAppend(std::forward<ARGS>(args)...);
        }
    };
}

#endif //OBJECT_ARRAY_SIMPLEAPPEND_H
