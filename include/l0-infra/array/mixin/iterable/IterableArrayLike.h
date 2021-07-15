//
// Created by Darwin Yuan on 2021/7/10.
//

#ifndef OBJECT_ARRAY_2_480C8FE86F4D471DADE80F708A386E46
#define OBJECT_ARRAY_2_480C8FE86F4D471DADE80F708A386E46

#include <l0-infra/array/iterator/Iterator.h>
#include <type_traits>

namespace mixin {
    template<typename T>
    struct IterableArrayLike : T {
        using typename T::SizeType;
        using typename T::ObjectType;

    private:
        using ConstIterator = iterator::Iterator<std::add_const_t<ObjectType>>;
        using Iterator      = iterator::Iterator<ObjectType>;

    public:
        auto begin() const -> ConstIterator {
            return {&T::GetObject(T::IndexBegin())};
        }

        auto end() const -> ConstIterator {
            return {&T::GetObject(T::IndexEnd())};
        }

        auto begin() -> Iterator {
            return {&T::GetObject(T::IndexBegin())};
        }

        auto end() -> Iterator {
            return {&T::GetObject(T::IndexEnd())};
        }
    };
}

#endif //OBJECT_ARRAY_2_480C8FE86F4D471DADE80F708A386E46
