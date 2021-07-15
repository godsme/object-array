//
// Created by Darwin Yuan on 2021/7/8.
//

#ifndef OBJECT_ARRAY_2_HOLDER_H
#define OBJECT_ARRAY_2_HOLDER_H

#include <cstdint>
#include <type_traits>

#define __dElEtE_cOpY_cOnS_aSsIgNmEnT() \
Holder(Holder const& rhs) = delete;       \
Holder(Holder&& rhs) = default;           \
auto operator=(Holder const& rhs) -> Holder& = delete; \
auto operator=(Holder&& rhs) -> Holder& = default

namespace holder::detail {
    template<typename OBJ, std::size_t MAX_NUM,
            template<typename, std::size_t> typename HOLDER,
            bool = std::is_trivially_destructible_v<OBJ>,
            bool = std::is_copy_constructible_v<OBJ>>
    struct Holder : HOLDER<OBJ, MAX_NUM> {
        using Parent = HOLDER<OBJ, MAX_NUM>;
        using Parent::Parent;
    };

    template<typename OBJ, std::size_t MAX_NUM,
            template<typename, std::size_t> typename HOLDER>
    struct Holder<OBJ, MAX_NUM, HOLDER, true, false>
            : HOLDER<OBJ, MAX_NUM> {
        using Parent = HOLDER<OBJ, MAX_NUM>;
        using Parent::Parent;

        // RULE OF FIVE!!!
        __dElEtE_cOpY_cOnS_aSsIgNmEnT();
    };

    template<typename OBJ, std::size_t MAX_NUM,
            template<typename, std::size_t> typename HOLDER>
    struct Holder<OBJ, MAX_NUM, HOLDER, false, true>
            : HOLDER<OBJ, MAX_NUM> {
        using Parent = HOLDER<OBJ, MAX_NUM>;
        using Parent::Parent;

        // RULE OF FIVE!!!
        Holder(Holder const& rhs) = default;
        auto operator=(Holder const& rhs) -> Holder& = default;

        Holder(Holder&& rhs) = default;
        auto operator=(Holder&& rhs) -> Holder& = default;

        ~Holder() { Parent::ClearContent(); }
    };

    template<typename OBJ, std::size_t MAX_NUM,
            template<typename, std::size_t> typename HOLDER>
    struct Holder<OBJ, MAX_NUM, HOLDER, false, false>
            : HOLDER<OBJ, MAX_NUM> {
        using Parent = HOLDER<OBJ, MAX_NUM>;
        using Parent::Parent;

        // RULE OF FIVE!!!
        __dElEtE_cOpY_cOnS_aSsIgNmEnT();
        ~Holder() { Parent::ClearContent(); }
    };
}

#endif //OBJECT_ARRAY_2_HOLDER_H
