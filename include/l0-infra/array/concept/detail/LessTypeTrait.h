//
// Created by Darwin Yuan on 2021/6/25.
//

#ifndef OBJECT_ARRAY_LESSTYPETRAIT_H
#define OBJECT_ARRAY_LESSTYPETRAIT_H

namespace _concept::detail {
    template<typename T>
    struct LessTypeTrait {
        using ObjectType = typename T::ObjectType;
        constexpr static auto less = [](ObjectType const&, ObjectType const&) -> bool { return true; };
    };
}

#endif //OBJECT_ARRAY_LESSTYPETRAIT_H
