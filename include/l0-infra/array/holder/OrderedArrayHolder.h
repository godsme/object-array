//
// Created by Darwin Yuan on 2021/7/9.
//

#ifndef OBJECT_ARRAY_2_ORDEREDARRAYHOLDER_6ACB7DA7BCD94B9B8EB1DD1A53F9EE66
#define OBJECT_ARRAY_2_ORDEREDARRAYHOLDER_6ACB7DA7BCD94B9B8EB1DD1A53F9EE66

#include <l0-infra/array/holder/detail/ObjectArrayHolder.h>
#include <l0-infra/array/holder/detail/Holder.h>
#include <l0-infra/array/mixin/less/OrderedArrayLike.h>

namespace holder::detail {
    template<typename OBJ, std::size_t MAX_NUM, typename LESS>
    class OrderedArrayHolder : LESS, public ObjectArrayHolder<OBJ, MAX_NUM, true> {
        using Parent = ObjectArrayHolder<OBJ, MAX_NUM, true>;

    public:
        using Parent::Parent;
        OrderedArrayHolder() : LESS{} {}

        template<typename ... ARGS>
        OrderedArrayHolder(LESS const& less, ARGS&& ... args)
            : LESS{less}
            , Parent(std::forward<ARGS>(args)...)
        {}

    private:
        template<typename>
        friend class mixin::OrderedArrayLike;

    protected:
        auto GetObjectLess() const -> LESS const& {
            return *this;
        }

        auto GetObjectLess() -> LESS& {
            return *this;
        }
    };

    template <typename LESS>
    struct OrderedArrayHolderAdapter {
        template<typename OBJ, std::size_t MAX_SIZE>
        using Type = OrderedArrayHolder<OBJ, MAX_SIZE, LESS>;
    };
}

namespace holder {
    template<typename OBJ, std::size_t MAX_NUM, typename LESS>
    using OrderedArrayHolder = detail::Holder<OBJ, MAX_NUM, detail::OrderedArrayHolderAdapter<LESS>::template Type>;
}

#endif //OBJECT_ARRAY_2_ORDEREDARRAYHOLDER_6ACB7DA7BCD94B9B8EB1DD1A53F9EE66
