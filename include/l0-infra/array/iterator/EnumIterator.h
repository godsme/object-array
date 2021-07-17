//
// Created by Darwin Yuan on 2021/7/17.
//

#ifndef OBJECT_ARRAY_7A917C3458964DF6B8C4EBF3BAEA3E3D
#define OBJECT_ARRAY_7A917C3458964DF6B8C4EBF3BAEA3E3D

#include <l0-infra/array/iterator/detail/IndexIterator.h>
#include <l0-infra/array/iterator/detail/PointerIterator.h>
#include <l0-infra/base/detail/CondConst.h>

namespace iterator {
    template<typename ARRAY, typename OBJ_TYPE>
    class EnumIterator {
        using SizeType = typename ARRAY::SizeType;
        struct Result {
            OBJ_TYPE& value;
            SizeType const index;
        };

    public:
        EnumIterator(ARRAY& array): array{array} {}

        auto operator*() const -> Result {
            return {array[index], index};
        }

        auto operator++() -> EnumIterator& {
            ++index;
            return *this;
        }

        auto operator!=(detail::IndexIterator<SizeType> const& rhs) const -> bool {
            return index != rhs.index;
        }

    protected:
        ARRAY& array;
        SizeType index{};
    };

    template<typename ARRAY>
    EnumIterator(ARRAY&) -> EnumIterator<ARRAY, ::detail::CondConst_t<std::is_const_v<ARRAY>, typename ARRAY::ObjectType>>;
}

#endif //OBJECT_ARRAY_7A917C3458964DF6B8C4EBF3BAEA3E3D
