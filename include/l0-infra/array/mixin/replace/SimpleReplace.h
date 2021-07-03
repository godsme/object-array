//
// Created by Darwin Yuan on 2021/7/3.
//

#ifndef OBJECT_ARRAY_SIMPLEREPLACE_H
#define OBJECT_ARRAY_SIMPLEREPLACE_H

#include <l0-infra/array/detail/ConceptDef.h>
#include <l0-infra/array/concept/ContiguousArrayLikeDataHolder.h>
#include <l0-infra/array/mixin/erase/SimpleDoErase.h>

namespace mixin {
    template<__cOnCePt(ContiguousArrayLikeDataHolder) T>
    class SimpleReplace : public T {
        using Self = T;

    public:
        using typename T::SizeType;
        using typename T::ObjectType;

    protected:
        using Self::Elems;

    private:
        template<typename ... ARGS>
        auto DoReplace(SizeType i, ARGS&& ... args) -> ObjectType* {
            auto* p = Self::Trait::Replace(Elems()[i], std::forward<ARGS>(args)...);
            if constexpr(Self::ORDERED) {
                return p;
            } else {
                return p;
            }
        }

    public:
        template<typename ... ARGS>
        auto Replace(SizeType i, ARGS &&... args) -> ObjectType * {
            return i < Self::Num() ? DoReplace(i, std::forward<ARGS>(args)...) : nullptr;
        }
    };
}

#endif //OBJECT_ARRAY_SIMPLEREPLACE_H
