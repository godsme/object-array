//
// Created by Darwin Yuan on 2021/7/12.
//

#ifndef OBJECT_ARRAY_2_A8DF38FD70854AC584FDBB75D22E683A
#define OBJECT_ARRAY_2_A8DF38FD70854AC584FDBB75D22E683A

#include <l0-infra/array/iterator/WithIndexScopeIterator.h>

namespace mixin {
    template<typename T>
    struct IterableWithIndexScopedArrayLike : T {
        using typename T::ArrayType;
        using typename T::SizeType;
        using typename T::ObjectType;
        using typename T::BitMap;

        using T::GetScope;
        using T::GetArray;

        using ConstIterator = iterator::WithIndexScopeIterator<ArrayType, BitMap, std::add_const_t<ObjectType>>;
        using Iterator = iterator::WithIndexScopeIterator<ArrayType, BitMap, ObjectType>;

        using EndIterator = iterator::EmptyIterator;

    public:
        auto begin() const -> ConstIterator {
            return {GetScope() >> T::GetArray().IndexBegin(), GetArray(), T::GetArray().IndexBegin()};
        }

        auto end() const -> EndIterator {
            return {};
        }

        auto begin() -> Iterator {
            return {GetScope() >> T::GetArray().IndexBegin(), GetArray(), T::GetArray().IndexBegin()};
        }

        auto end() -> EndIterator {
            return {};
        }
    };
}

#endif //OBJECT_ARRAY_2_A8DF38FD70854AC584FDBB75D22E683A
