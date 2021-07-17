//
// Created by Darwin Yuan on 2021/7/17.
//

#ifndef OBJECT_ARRAY_581CC207464B45AF9BCA97B2F5A07C83
#define OBJECT_ARRAY_581CC207464B45AF9BCA97B2F5A07C83

#include <l0-infra/array/iterator/EnumIterator.h>

namespace mixin {
    template<typename T>
    struct IterableEnumArrayLike : T {
        using Self = T;
    public:
        using typename T::SizeType;
        using typename T::ObjectType;

    public:
        auto begin() const -> auto {
            return iterator::EnumIterator{T::GetArray()};
        }

        auto end() const -> auto {
            return iterator::detail::IndexIterator{T::GetArray().GetNum()};
        }

        auto begin() -> auto {
            return iterator::EnumIterator{T::GetArray()};
        }

        auto end() -> auto {
            return iterator::detail::IndexIterator{T::GetArray().GetNum()};
        }
    };
}

#endif //OBJECT_ARRAY_581CC207464B45AF9BCA97B2F5A07C83
