//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_DEFMIXIN_H
#define OBJECT_ARRAY_DEFMIXIN_H

#include <cub/base/DeduceOffsetType.h>
#include <object-array/ArrayOffset.h>
#include <type_traits>

namespace mixin {
    namespace detail {
        template<typename T, bool = std::is_empty_v<T>>
        struct Extends : T::Concept {
            // T must be data holder
            using DataHolder = T;
            using SizeType = typename T::SizeType;
            constexpr static SizeType MAX_SIZE = T::MAX_SIZE;
            using OffsetType = ArrayOffset<DeduceOffsetType_t<MAX_SIZE>, SizeType>;
            using EndOffsetType = ArrayEndOffset<DeduceOffsetType_t<MAX_SIZE>, SizeType>;
        };

        template<typename T>
        struct Extends<T, true> : T {};
    }
}

#define __Def_Mixin(Mixin, Concept) \
    template<Concept T, typename Self = detail::Extends<T>> \
    struct Mixin : Self

#define __Def_Mixin_Composite(Mixin, Concept, Composite) \
    template<Concept T, typename Self = detail::Extends<Composite<T>>> \
    struct Mixin : Self

#endif //OBJECT_ARRAY_DEFMIXIN_H
