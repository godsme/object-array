//
// Created by Darwin Yuan on 2021/7/11.
//

#ifndef OBJECT_ARRAY_2_506630827B1E42CFBC1988D1CE5542CA
#define OBJECT_ARRAY_2_506630827B1E42CFBC1988D1CE5542CA

#include <l0-infra/array/holder/detail/ViewHolder.h>
#include <l0-infra/array/holder/detail/ArrayLikeViewHolder.h>
#include <l0-infra/array/mixin/array_like/ScopedArrayLike.h>

namespace holder::detail {
    template<typename ARRAY, typename ARRAY_HOLDER>
    class ScopeViewHolder : public ViewHolder<ARRAY, ARRAY_HOLDER> {
        using Parent = ViewHolder<ARRAY, ARRAY_HOLDER>;

    public:
        using typename Parent::SizeType;
        using BitMap = ::detail::ArrayScope<Parent::MAX_SIZE>;

        ScopeViewHolder(BitMap scope) : scope{scope} {}

    private:
        template<typename>
        friend class mixin::ScopedArrayLike;

    private:
        BitMap scope;
    };
}

namespace holder {
    template<typename ARRAY>
    using ScopeView = detail::ArrayLikeViewHolder<ARRAY, detail::ScopeViewHolder>;
}

#endif //OBJECT_ARRAY_2_506630827B1E42CFBC1988D1CE5542CA
