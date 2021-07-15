//
// Created by Darwin Yuan on 2021/7/13.
//

#ifndef OBJECT_ARRAY_2_12728AE81EA84C559E606ED50C116B13
#define OBJECT_ARRAY_2_12728AE81EA84C559E606ED50C116B13

#include <type_traits>

#define bInArY_oP_dEtEcT(name, op) \
template <typename T, typename = void> \
struct name : std::false_type {}; \
template <typename T> \
struct name<T, std::void_t<decltype(std::declval<T const&>() op std::declval<T const&>())>> : std::true_type {}

bInArY_oP_dEtEcT(IsEqualComparable, ==);
bInArY_oP_dEtEcT(IsNotEqComparable, !=);
bInArY_oP_dEtEcT(IsLessThanComparable, <);
bInArY_oP_dEtEcT(IsGreaterThanComparable, >);
bInArY_oP_dEtEcT(IsLessEqComparable, <=);
bInArY_oP_dEtEcT(IsGreaterEqComparable, >=);

namespace detail::equality {
    template<typename T>
    constexpr bool IS_EQ_COMPARABLE =
                IsEqualComparable<T>::value ||
                IsNotEqComparable<T>::value ||
                IsLessThanComparable<T>::value ||
                IsGreaterThanComparable<T>::value ||
                IsLessEqComparable<T>::value ||
                IsGreaterEqComparable<T>::value;

    template<typename T>
    constexpr auto GetEqualityCompareFunction() -> auto {
        if constexpr(IsEqualComparable<T>::value) {
            return [](T const& l, T const& r) -> bool { return l == r; };
        } else if constexpr(IsNotEqComparable<T>::value) {
            return [](T const& l, T const& r) -> bool { return !(l != r); };
        } else if constexpr(IsLessThanComparable<T>::value) {
            return [](T const& l, T const& r) -> bool { return !(l < r || r < l); };
        } else if constexpr(IsGreaterThanComparable<T>::value) {
            return [](T const& l, T const& r) -> bool { return !(l > r || r > l); };
        } else if constexpr(IsLessEqComparable<T>::value) {
            return [](T const& l, T const& r) -> bool { return (l <= r && r <= l); };
        } else if constexpr(IsGreaterEqComparable<T>::value) {
            return [](T const& l, T const& r) -> bool { return (l >= r && r >= l); };
        } else {
            static_assert(IS_EQ_COMPARABLE<T>, "Equality cannot be compared");
        }
    }

    template<typename T>
    constexpr auto EQ_COMPARE = GetEqualityCompareFunction<T>();
}

namespace detail::less {
    template<typename T>
    constexpr bool IS_LESS_COMPARABLE =
            IsLessThanComparable<T>::value ||
            IsGreaterThanComparable<T>::value ||
            IsLessEqComparable<T>::value ||
            IsGreaterEqComparable<T>::value;

    template<typename T>
    constexpr auto GetLessCompareFunction() -> auto {
        if constexpr(IsLessThanComparable<T>::value) {
            return [](T const& l, T const& r) -> bool { return l < r; };
        } else if constexpr(IsGreaterThanComparable<T>::value) {
            return [](T const& l, T const& r) -> bool { return r > l; };
        } else if constexpr(IsLessEqComparable<T>::value) {
            return [](T const& l, T const& r) -> bool { return !(r <= l); };
        } else if constexpr(IsGreaterEqComparable<T>::value) {
            return [](T const& l, T const& r) -> bool { return !(l >= r); };
        } else {
            static_assert(IS_LESS_COMPARABLE<T>, "Equality cannot be compared");
        }
    }

    template<typename T>
    constexpr auto LESS_COMPARE = GetLessCompareFunction<T>();
}

#endif //OBJECT_ARRAY_2_12728AE81EA84C559E606ED50C116B13
