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

    protected:
        using Self::GetArray;
        using Self::IndexBegin;
        using Self::IndexEnd;

    public:
        template<typename ... ARGS>
        auto Replace(SizeType i, ARGS &&... args) -> ObjectType * {
            if(i < IndexBegin() || i >= IndexEnd()) return nullptr;
            return GetArray().Replace(IndexBegin() + i, std::forward<ARGS>(args)...);
        }
    };
}

#endif //OBJECT_ARRAY_RANGEDREPLACE_H
