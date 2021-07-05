//
// Created by Darwin Yuan on 2021/7/6.
//

#ifndef OBJECT_ARRAY_DYNAMICALLOCATOR_H
#define OBJECT_ARRAY_DYNAMICALLOCATOR_H

#include <l0-infra/array/detail/config.h>

#if HAS_CONCEPT
#include <concepts>

namespace _concept {
    template<typename T>
    concept DynamicAllocator = requires(T& o, typename T::ObjectType const& obj, typename T::ObjectType&& r_obj) {
        { o.Append(obj) } -> std::same_as<typename T::ObjectType*>;
        { o.Append(std::move(r_obj)) } -> std::same_as<typename T::ObjectType*>;
        { o.Remove(&obj) } -> std::same_as<void>;
        { o.ReplaceObj(&obj, obj) } -> std::same_as<typename T::ObjectType*>;
        { o.ReplaceObj(&obj, std::move(r_obj)) } -> std::same_as<typename T::ObjectType*>;
        { o.HasEnoughSlots(100) } -> std::same_as<bool>;
    };
};

#endif

#endif //OBJECT_ARRAY_DYNAMICALLOCATOR_H
