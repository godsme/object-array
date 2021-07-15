//
// Created by Darwin Yuan on 2021/7/10.
//

#ifndef OBJECT_ARRAY_2_261B3A170075439ABDDB0FDCDB296778
#define OBJECT_ARRAY_2_261B3A170075439ABDDB0FDCDB296778

#include <l0-infra/array/holder/detail/ViewHolder.h>
#include <l0-infra/array/holder/detail/ArrayLikeViewHolder.h>
#include <l0-infra/array/detail/ArrayIndices.h>
#include <l0-infra/array/mixin/array_like/IndexedArrayLike.h>
#include <l0-infra/array/mixin/array_like/ViewedArray.h>

namespace holder::detail {
    template<typename ARRAY, typename ARRAY_HOLDER>
    class SortView : public ViewHolder<ARRAY, ARRAY_HOLDER> {
        using Parent = ViewHolder<ARRAY, ARRAY_HOLDER>;

    public:
        constexpr static auto IS_CONST = false;
        constexpr static auto IS_ORDERED = true;

        auto GetIndices() const -> decltype(auto) { return (indices); }

    private:
        auto GetIndices() -> decltype(auto) { return (indices); }

    private:
        template<typename> friend class mixin::IndexedArrayLike;
        template<typename> friend class mixin::ViewedArray;

    private:
        array_indices::Array<Parent::MAX_SIZE> indices;
    };
}

namespace holder {
    template<typename ARRAY>
    using SortView = detail::ArrayLikeViewHolder<ARRAY, detail::SortView>;
}

#endif //OBJECT_ARRAY_2_261B3A170075439ABDDB0FDCDB296778
