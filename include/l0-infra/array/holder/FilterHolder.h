//
// Created by Darwin Yuan on 2021/7/17.
//

#ifndef OBJECT_ARRAY_D616F31F467645D1968B7C23F3E2E6C6
#define OBJECT_ARRAY_D616F31F467645D1968B7C23F3E2E6C6

#include <l0-infra/array/holder/detail/ViewHolder.h>
#include <l0-infra/array/holder/detail/ArrayLikeViewHolder.h>

namespace holder::detail {
    template<typename ARRAY, typename ARRAY_HOLDER, typename PRED>
    struct FilterHolder : private PRED, detail::ViewHolder<ARRAY, ARRAY_HOLDER> {
        explicit FilterHolder(PRED const& pred) : PRED(pred) {}
    };

    template<typename PRED>
    struct Filter {
        template<typename ARRAY, typename ARRAY_HOLDER>
        using Type = FilterHolder<ARRAY, ARRAY_HOLDER, PRED>;
    };
}

namespace holder {
    template<typename ARRAY>
    using Filter = detail::ArrayLikeViewHolder<ARRAY, detail::Filter::template Type>;
}

#endif //OBJECT_ARRAY_D616F31F467645D1968B7C23F3E2E6C6
