//
// Created by Darwin Yuan on 2021/6/24.
//

#ifndef OBJECT_ARRAY_SCOPEDFOREACHEXT_H
#define OBJECT_ARRAY_SCOPEDFOREACHEXT_H

#include <object-array/mixin/ScopedForEach.h>
#include <utility>

namespace mixin {
    template<_concept::OpVisitable T>
    class ScopedForEachExt : public ScopedForEach<T> {
        using Self = ScopedForEach<T>;

    public:
        using BitMap = typename Self::BitMap;
        using ObjectType = typename Self::ObjectType;
        using SizeType = typename Self::SizeType;

    public:
        using Self::ForEach;

        template<_concept::Op<ObjectType, SizeType> OP>
        auto ForEach(BitMap scope, OP &&op) const -> auto {
            return Self::template DoForEach<false, true>(scope, std::forward<OP>(op));
        }

        template<_concept::Op<ObjectType, SizeType> OP>
        auto ForEach(BitMap scope, OP &&op) -> auto {
            return Self::template DoForEach<true, true>(scope, std::forward<OP>(op));
        }

        template<_concept::Op<ObjectType, SizeType> OP>
        auto ForEachEx(BitMap excluded, OP &&op) const -> auto {
            return ForEach(~excluded, std::forward<OP>(op));
        }

        template<_concept::Op<ObjectType, SizeType> OP>
        auto ForEachEx(BitMap excluded, OP &&op) -> auto {
            return ForEach(~excluded, std::forward<OP>(op));
        }
    };
}

#endif //OBJECT_ARRAY_SCOPEDFOREACHEXT_H
