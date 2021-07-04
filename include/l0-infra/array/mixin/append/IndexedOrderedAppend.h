//
// Created by Darwin Yuan on 2021/7/3.
//

#ifndef OBJECT_ARRAY_INDEXEDORDEREDAPPEND_H
#define OBJECT_ARRAY_INDEXEDORDEREDAPPEND_H

#include <l0-infra/array/detail/ConceptDef.h>
#include <l0-infra/array/concept/ContiguousArrayLikeDataHolder.h>

namespace mixin {
    template<__cOnCePt(ConstContiguousArrayLikeDataHolder) T>
    class IndexedOrderedAppend : public T {
        using Self = T;

    public:
        using typename T::SizeType;
        using typename T::ObjectType;

        static constexpr auto MAX_SIZE = T::MAX_SIZE;

    protected:
        using Self::GetIndices;
        using Self::Elems;
        using Self::Num;
        using typename Self::Trait;
        using Self::ConstElemToObject;

    private:
        template<typename ... ARGS>
        auto ActualAppend(ARGS&& ... args) -> ObjectType* {
            auto* p = Self::Append(std::forward<ARGS>(args)...);
            GetIndices().DoAppend(Self::GetLess(), Num());
            return p;
        }

    public:
        template<typename ... ARGS>
        auto DoAppend(ARGS &&... args) -> ObjectType * {
            return Num() < MAX_SIZE ? ActualAppend(std::forward<ARGS>(args)...) : nullptr;
        }
    };
}

#endif //OBJECT_ARRAY_INDEXEDORDEREDAPPEND_H
