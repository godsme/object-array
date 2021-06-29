//
// Created by Darwin Yuan on 2021/6/29.
//

#ifndef OBJECT_ARRAY_RANGEDREPLACE_H
#define OBJECT_ARRAY_RANGEDREPLACE_H

#include <l0-infra/array/concept/ContinuousArrayLikeDataHolder.h>

namespace mixin {
    template<typename T>
    class RangedReplace : public T {
        using Self = T;

    public:
        using typename T::SizeType;
        using typename T::ObjectType;
        using typename T::Trait;

        static constexpr auto MAX_SIZE = T::MAX_SIZE;

    protected:
        using Self::GetObj;

    public:
        template<typename ... ARGS>
        auto Replace(SizeType i, ARGS &&... args) -> ObjectType * {
            return i < Num() ? Trait::Replace(Elems()[i], std::forward<ARGS>(args)...) : nullptr;
        }
    };
}

#endif //OBJECT_ARRAY_RANGEDREPLACE_H
