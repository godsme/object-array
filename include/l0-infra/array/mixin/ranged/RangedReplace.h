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
            auto index = i + IndexBegin();
            return i >= IndexEnd() ? nullptr : GetArray().Replace(index, std::forward<ARGS>(args)...);
        }
    };
}

#endif //OBJECT_ARRAY_RANGEDREPLACE_H
