//
// Created by Darwin Yuan on 2021/7/17.
//

#ifndef OBJECT_ARRAY_F0DAC6903F674F10B9E8E60C4E1919EC
#define OBJECT_ARRAY_F0DAC6903F674F10B9E8E60C4E1919EC

#include <l0-infra/array/iterator/detail/ScopeIterator.h>
#include <l0-infra/array/iterator/EnumIterator.h>

namespace iterator::detail {
    template<typename ARRAY, typename OBJ_TYPE>
    class ScopeEnumIterator {
        using SizeType = typename ARRAY::SizeType;
        struct Result {
            OBJ_TYPE& value;
            SizeType const index;
        };

    public:
        ScopeEnumIterator(ARRAY& array): array{array} {}

        auto operator*() const -> Result {
            return {array[index], enumIndex};
        }

    protected:
        auto StepForward() -> void {
            ++index;
            ++enumIndex;
        }

        auto SkipForward() -> void { ++index; }

    protected:
        ARRAY& array;
        SizeType index{};
        SizeType enumIndex{};
    };
}

namespace iterator {
    template<typename ARRAY, typename BIT_MAP, typename OBJ_TYPE>
    using ScopeEnumIterator = detail::ScopeIterator<detail::ScopeEnumIterator<ARRAY, OBJ_TYPE>, BIT_MAP>;
}

#endif //OBJECT_ARRAY_F0DAC6903F674F10B9E8E60C4E1919EC
