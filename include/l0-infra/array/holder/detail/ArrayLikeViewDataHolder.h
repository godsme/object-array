//
// Created by Darwin Yuan on 2021/6/23.
//

#ifndef OBJECT_ARRAY_ARRAYLIKEVIEWDATAHOLDER_H
#define OBJECT_ARRAY_ARRAYLIKEVIEWDATAHOLDER_H

#include <utility>

namespace holder::detail {
    template<typename ARRAY, typename OWNER, template <typename, typename, typename> typename SUPER>
    struct RefViewDataHolder : SUPER<ARRAY, OWNER, RefViewDataHolder<ARRAY, OWNER, SUPER>> {
        using Parent = SUPER<ARRAY,OWNER,  RefViewDataHolder<ARRAY, OWNER, SUPER>>;

    public:
        template<typename ... ARGS>
        RefViewDataHolder(ARRAY& array, ARGS&& ... args)
            : Parent(std::forward<ARGS>(args)...), array{array} {}

        auto GetArray() const -> ARRAY& { return array; }
        auto GetArray() -> ARRAY& { return array; }

    protected:
        ARRAY& array;
    };

    template<typename ARRAY, typename OWNER, template <typename, typename, typename> typename SUPER>
    struct ValueViewDataHolder : SUPER<ARRAY, OWNER, ValueViewDataHolder<ARRAY, OWNER, SUPER>> {
        using Parent = SUPER<ARRAY, OWNER, ValueViewDataHolder<ARRAY, OWNER, SUPER>>;

        static_assert(std::is_move_constructible_v<ARRAY>);

    public:
        template<typename ... ARGS>
        ValueViewDataHolder(ARRAY&& array, ARGS&& ... args)
                : Parent(std::forward<ARGS>(args)...), array{std::move(array)} {}

        auto GetArray() const -> ARRAY const& { return array; }
        auto GetArray() -> ARRAY& { return array; }

    protected:
        ARRAY array;
    };
}

#endif //OBJECT_ARRAY_ARRAYLIKEVIEWDATAHOLDER_H
