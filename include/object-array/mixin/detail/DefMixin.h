//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_DEFMIXIN_H
#define OBJECT_ARRAY_DEFMIXIN_H

#include <cub/base/DeduceOffsetType.h>
#include <cub/base/BitSet.h>
#include <cub/base/detail/DeduceIntOptional.h>
#include <object-array/ArrayOffset.h>
#include <type_traits>

namespace mixin {
    namespace detail {
        template<typename T, bool = std::is_empty_v<T>>
        struct Extends : T::Interface {
            // T must be the data holder
            using DataHolder = T;
            using SizeType = typename T::SizeType;
            constexpr static SizeType MAX_SIZE = T::MAX_SIZE;
            using BitMap = BitSet<MAX_SIZE>;
            using Maybe = ::detail::DeduceIntOptional_t<MAX_SIZE>;
            using OffsetType = ArrayOffset<DeduceOffsetType_t<MAX_SIZE>, SizeType>;
            using EndOffsetType = ArrayEndOffset<DeduceOffsetType_t<MAX_SIZE>, SizeType>;
        };

        template<typename T>
        struct Extends<T, true> : T {};
    }
}

#endif //OBJECT_ARRAY_DEFMIXIN_H
