//
// Created by Darwin Yuan on 2021/6/24.
//

#ifndef OBJECT_ARRAY_SIMPLEFOREACHEXT_H
#define OBJECT_ARRAY_SIMPLEFOREACHEXT_H

namespace mixin {
    template<typename T>
    class SimpleForEachExt : public T {
        using Self = T;
    public:
        using typename Self::SizeType;
        using typename Self::ObjectType;

    public:
        template<_concept::Op<ObjectType, SizeType> OP>
        auto ForEach(OP &&op) const -> auto {
            return Self::template DoForEach<false>(std::forward<OP>(op));
        }

        template<_concept::Op<ObjectType, SizeType> OP>
        auto ForEach(OP &&op) -> auto {
            return Self::template DoForEach<true>(std::forward<OP>(op));
        }
    };
}

#endif //OBJECT_ARRAY_SIMPLEFOREACHEXT_H
