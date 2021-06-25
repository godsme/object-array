//
// Created by Darwin Yuan on 2021/6/24.
//

#ifndef OBJECT_ARRAY_OP_H
#define OBJECT_ARRAY_OP_H

#include <object-array/config.h>
#if HAS_CONCEPT
#include <concepts>
#include <type_traits>

namespace _concept {
    template<typename OP, typename ObjectType>
    concept SimpleOp = requires(OP&& op, ObjectType& obj) {
        { op(obj) };
    };

    template<typename OP, typename ObjectType, typename SizeType>
    concept WithIndexOp = requires(OP&& op, ObjectType& obj, SizeType n) {
        { op(obj, n) };
    };

    template<typename OP, typename ObjectType, typename SizeType>
    concept Op = WithIndexOp<OP, ObjectType, SizeType> || SimpleOp<OP, ObjectType>;
}
#endif

#endif //OBJECT_ARRAY_OP_H
