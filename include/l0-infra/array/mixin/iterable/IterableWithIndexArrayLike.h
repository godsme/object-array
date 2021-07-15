//
// Created by Darwin Yuan on 2021/7/10.
//

#ifndef OBJECT_ARRAY_2_3D4835B55341430888211C9DC9022354
#define OBJECT_ARRAY_2_3D4835B55341430888211C9DC9022354

#include <l0-infra/array/iterator/WithIndexIterator.h>

namespace mixin {
    template<typename T>
    struct IterableWithIndexArrayLike : T {
        using Self = T;
    public:
        using typename T::SizeType;
        using typename T::ObjectType;

    public:
        auto begin() const -> auto {
            return iterator::WithIndexIterator{T::GetArray(), T::IndexBegin()};
        }

        auto end() const -> auto {
            return iterator::WithIndexIterator{T::GetArray(), T::IndexEnd()};
        }

        auto begin() -> auto {
            return iterator::WithIndexIterator{T::GetArray(), T::IndexBegin()};
        }

        auto end() -> auto {
            return iterator::WithIndexIterator{T::GetArray(), T::IndexEnd()};
        }
    };
}

#endif //OBJECT_ARRAY_2_3D4835B55341430888211C9DC9022354
