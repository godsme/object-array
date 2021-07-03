//
// Created by Darwin Yuan on 2021/7/2.
//

#ifndef OBJECT_ARRAY_ORDEREDAPPEND_H
#define OBJECT_ARRAY_ORDEREDAPPEND_H

#include <l0-infra/array/detail/ConceptDef.h>
#include <l0-infra/array/mixin/append/OrderedDoAppend.h>

namespace mixin {
    template<__cOnCePt(ContinuousArrayLikeDataHolder) T>
    class OrderedAppend : public OrderedDoAppend<T> {
        using Self = OrderedDoAppend<T>;

    public:
        using typename T::SizeType;
        using typename T::ObjectType;

        static constexpr auto MAX_SIZE = T::MAX_SIZE;

    protected:
        using Self::Num;
        using typename Self::Compare;

    public:
        template<typename ... ARGS>
        auto Append(ARGS &&... args) -> ObjectType * {
            return Num() < MAX_SIZE ? Self::DoAppend(Compare{}, std::forward<ARGS>(args)...) : nullptr;
        }
    };
}

#endif //OBJECT_ARRAY_ORDEREDAPPEND_H