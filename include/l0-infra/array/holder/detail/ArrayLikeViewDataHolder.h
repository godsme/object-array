//
// Created by Darwin Yuan on 2021/6/23.
//

#ifndef OBJECT_ARRAY_ARRAYLIKEVIEWDATAHOLDER_H
#define OBJECT_ARRAY_ARRAYLIKEVIEWDATAHOLDER_H

#include <utility>

namespace holder::detail {
    template<typename ARRAY, template <typename, typename, bool> typename SUPER, bool ORDERED>
    struct RefViewDataHolder : SUPER<ARRAY, RefViewDataHolder<ARRAY, SUPER, ORDERED>, ORDERED> {
        using Parent = SUPER<ARRAY,RefViewDataHolder<ARRAY, SUPER, ORDERED>, ORDERED>;

    public:
        template<typename ... ARGS>
        RefViewDataHolder(ARRAY& array, ARGS&& ... args)
            : Parent(std::forward<ARGS>(args)...), array{array} {}

        auto GetArray() const -> ARRAY& { return array; }
        auto GetArray() -> ARRAY& { return array; }

    protected:
        ARRAY& array;
    };

    template<typename ARRAY, template <typename, typename, bool> typename SUPER, bool ORDERED>
    struct ValueViewDataHolder : SUPER<ARRAY, ValueViewDataHolder<ARRAY, SUPER, ORDERED>, ORDERED> {
        using Parent = SUPER<ARRAY, ValueViewDataHolder<ARRAY, SUPER, ORDERED>, ORDERED>;

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
