//
// Created by Darwin Yuan on 2021/6/24.
//

#ifndef OBJECT_ARRAY_PREDTYPETRAIT_H
#define OBJECT_ARRAY_PREDTYPETRAIT_H

namespace _concept::detail {
    template<typename T>
    struct PredTypeTrait {
        using ObjectType = typename T::ObjectType;
        constexpr static auto pred = [](ObjectType const&) -> bool { return true; };
        using Type = decltype(pred);
    };
}

#endif //OBJECT_ARRAY_PREDTYPETRAIT_H
