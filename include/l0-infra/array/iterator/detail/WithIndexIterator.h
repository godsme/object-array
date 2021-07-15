//
// Created by Darwin Yuan on 2021/7/10.
//

#ifndef OBJECT_ARRAY_2_BD8D0F3FA3B945DEA1A3581183EDC6D9
#define OBJECT_ARRAY_2_BD8D0F3FA3B945DEA1A3581183EDC6D9

#include <l0-infra/array/iterator/detail/IndexIterator.h>
#include <l0-infra/array/iterator/detail/PointerIterator.h>

namespace iterator::detail {
    template<typename ARRAY, typename OBJ_TYPE, typename BASE_ITERATOR>
    class WithIndexIterator : public BASE_ITERATOR {
        using SizeType = typename ARRAY::SizeType;
        struct Result {
            OBJ_TYPE& value;
            SizeType const index;
        };

    public:
        template<typename ... ARGS>
        WithIndexIterator(ARRAY& array, ARGS&& ... args)
            : BASE_ITERATOR(std::forward<ARGS>(args)...), array{array} {}

        auto operator*() const -> Result {
            auto index = BASE_ITERATOR::GetValue();
            return {array.GetObject(index), index};
        }

    protected:
        ARRAY& array;
    };

    template<typename ARRAY, typename OBJ_TYPE>
    using ByIndexWithIndexIterator = detail::WithIndexIterator<ARRAY, OBJ_TYPE, detail::IndexIterator<typename ARRAY::SizeType>>;

    template<typename ARRAY, typename OBJ_TYPE>
    using ByPointerWithIndexIterator = detail::WithIndexIterator<ARRAY, OBJ_TYPE, detail::PointerIterator<typename ARRAY::SizeType>>;
}

#endif //OBJECT_ARRAY_2_BD8D0F3FA3B945DEA1A3581183EDC6D9
