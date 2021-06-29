//
// Created by Darwin Yuan on 2021/6/25.
//

#ifndef OBJECT_ARRAY_LESSTYPETRAIT_H
#define OBJECT_ARRAY_LESSTYPETRAIT_H

namespace _concept::detail {
    template<typename T>
    struct LessTypeTrait : T {
        using ObjectType = typename T::ObjectType;
        constexpr static auto pred = [](ObjectType const&, ObjectType const&) -> bool { return true; };
        using Type = decltype(pred);
    };
}

#endif //OBJECT_ARRAY_LESSTYPETRAIT_H
