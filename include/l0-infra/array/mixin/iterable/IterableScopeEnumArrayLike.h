//
// Created by Darwin Yuan on 2021/7/17.
//

#ifndef OBJECT_ARRAY_9C0A882A65194312BEFA6DA0F7B0813B
#define OBJECT_ARRAY_9C0A882A65194312BEFA6DA0F7B0813B

#include <l0-infra/array/iterator/ScopeEnumIterator.h>

namespace mixin {
    template<typename T>
    struct IterableScopeEnumArrayLike : T {
        using typename T::SizeType;
        using typename T::ObjectType;
        using typename T::ArrayType;

    private:
        using ConstIterator = iterator::ScopeEnumIterator<ArrayType, typename ArrayType::BitMap, ObjectType const>;
        using Iterator = iterator::ScopeEnumIterator<ArrayType, typename ArrayType::BitMap, ObjectType>;

    public:
        auto begin() const -> ConstIterator {
            return {T::GetScope() >> T::GetArray().IndexBegin(), T::GetArray()};
        }

        auto end() const -> iterator::EmptyIterator {
            return {};
        }

        auto begin() -> Iterator {
            return {T::GetScope() >> T::GetArray().IndexBegin(), T::GetArray()};
        }

        auto end() -> iterator::EmptyIterator {
            return {};
        }
    };
}

#endif //OBJECT_ARRAY_9C0A882A65194312BEFA6DA0F7B0813B
