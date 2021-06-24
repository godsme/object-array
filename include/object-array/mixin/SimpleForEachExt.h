//
// Created by Darwin Yuan on 2021/6/24.
//

#ifndef OBJECT_ARRAY_SIMPLEFOREACHEXT_H
#define OBJECT_ARRAY_SIMPLEFOREACHEXT_H

#include <object-array/mixin/SimpleForEach.h>

namespace mixin {
    template<_concept::OpVisitable T>
    class SimpleForEachExt : public SimpleForEach<T> {
        using Self = SimpleForEach<T>;

    public:
        using SizeType = typename Self::SizeType;
        using ObjectType = typename Self::ObjectType;

    public:
        template<_concept::Op<ObjectType, SizeType> OP>
        auto ForEach(OP &&op) const -> auto {
            return Self::template ForEach<false>(std::forward<OP>(op));
        }

        template<_concept::Op<ObjectType, SizeType> OP>
        auto ForEach(OP &&op) -> auto {
            return Self::template ForEach<true>(std::forward<OP>(op));
        }
    };
}

#endif //OBJECT_ARRAY_SIMPLEFOREACHEXT_H
