//
// Created by Darwin Yuan on 2021/7/12.
//

#ifndef OBJECT_ARRAY_2_2EBE75B5706048A1A53D2E9D7F78E2B6
#define OBJECT_ARRAY_2_2EBE75B5706048A1A53D2E9D7F78E2B6

#include <l0-infra/array/iterator/detail/IndexIterator.h>
#include <l0-infra/array/iterator/detail/PointerIterator.h>
#include <l0-infra/array/iterator/detail/ViewIterator.h>

namespace iterator::detail {
    template<typename ARRAY, typename OBJ_TYPE, typename BASE_ITERATOR>
    struct IndexBasedIterator : ViewIterator<ARRAY, OBJ_TYPE, BASE_ITERATOR> {
        using Parent = ViewIterator<ARRAY, OBJ_TYPE, BASE_ITERATOR>;
        using SizeType = typename ARRAY::SizeType;

        using Parent::Parent;

        auto operator++() -> IndexBasedIterator& {
            BASE_ITERATOR::StepForward();
            return *this;
        }

        auto operator*() -> OBJ_TYPE& {
            return Parent::GetValue();
        }
    };
}

namespace iterator {
    template<typename ARRAY, typename OBJ_TYPE, typename SIZE_TYPE>
    using IndicesBasedIndexIterator = detail::IndexBasedIterator<ARRAY, OBJ_TYPE, detail::IndexIterator<SIZE_TYPE>>;

    template<typename ARRAY, typename OBJ_TYPE, typename SIZE_TYPE>
    using PointerBasedIndexIterator = detail::IndexBasedIterator<ARRAY, OBJ_TYPE, detail::PointerIterator<SIZE_TYPE>>;
}

#endif //OBJECT_ARRAY_2_2EBE75B5706048A1A53D2E9D7F78E2B6
