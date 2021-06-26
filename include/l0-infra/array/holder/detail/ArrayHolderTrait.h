//
// Created by Darwin Yuan on 2021/6/24.
//

#ifndef OBJECT_ARRAY_ARRAYHOLDERTRAIT_H
#define OBJECT_ARRAY_ARRAYHOLDERTRAIT_H

#include <cstdint>
#include <type_traits>

//
// ObjectArray always support move cons/assignment even if T does not
// support move ops.
// 'coz all we do about move is move/copy all elements of the SOURCE, then
// clear the SOURCE. It doesn't matter that T itself supports move or copy.
// we pass the r-value reference to its constructor, either move or copy cons
// will accept it (as long as one of them exists). If both don't exists. compiling
// would fail.
//

#define __dElEtE_cOpY_cOnS_aSsIgNmEnT() \
Holder(Holder const& rhs) = delete;       \
Holder(Holder&& rhs) = default;           \
auto operator=(Holder const& rhs) -> Holder& = delete; \
auto operator=(Holder&& rhs) -> Holder& = default

namespace holder::detail {
    template<typename OBJ, std::size_t MAX_NUM, typename OWNER,
            template<typename, std::size_t, typename> typename HOLDER,
            bool = std::is_trivially_destructible_v<OBJ>,
            bool = std::is_copy_constructible_v<OBJ>>
    struct Holder : HOLDER<OBJ, MAX_NUM, OWNER> {
        using Parent = HOLDER<OBJ, MAX_NUM, OWNER>;
        using Parent::Parent;
    };

    template<typename OBJ, std::size_t MAX_NUM, typename OWNER,
            template<typename, std::size_t, typename> typename HOLDER>
    struct Holder<OBJ, MAX_NUM, OWNER, HOLDER, true, false> : HOLDER<OBJ, MAX_NUM, OWNER> {
        using Parent = HOLDER<OBJ, MAX_NUM, OWNER>;
        using Parent::Parent;

        // RULE OF FIVE!!!
        __dElEtE_cOpY_cOnS_aSsIgNmEnT();
    };

    template<typename OBJ, std::size_t MAX_NUM, typename OWNER,
            template<typename, std::size_t, typename> typename HOLDER>
    struct Holder<OBJ, MAX_NUM, OWNER, HOLDER, false, true> : HOLDER<OBJ, MAX_NUM, OWNER> {
        using Parent = HOLDER<OBJ, MAX_NUM, OWNER>;
        using Parent::Parent;

        // RULE OF FIVE!!!
        Holder(Holder const& rhs) = default;
        auto operator=(Holder const& rhs) -> Holder& = default;

        Holder(Holder&& rhs) = default;
        auto operator=(Holder&& rhs) -> Holder& = default;

        ~Holder() { Parent::ClearContent(); }
    };

    template<typename OBJ, std::size_t MAX_NUM, typename OWNER,
            template<typename, std::size_t, typename> typename HOLDER>
    struct Holder<OBJ, MAX_NUM, OWNER, HOLDER, false, false> : HOLDER<OBJ, MAX_NUM, OWNER> {
        using Parent = HOLDER<OBJ, MAX_NUM, OWNER>;
        using Parent::Parent;

        // RULE OF FIVE!!!
        __dElEtE_cOpY_cOnS_aSsIgNmEnT();
        ~Holder() { Parent::ClearContent(); }
    };
}

#endif //OBJECT_ARRAY_ARRAYHOLDERTRAIT_H
