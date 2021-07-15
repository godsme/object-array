//
// Created by Darwin Yuan on 2021/7/9.
//

#ifndef OBJECT_ARRAY_2_CONDCONST_A4E5523D399943E5BC4DE43C7B1CDE48
#define OBJECT_ARRAY_2_CONDCONST_A4E5523D399943E5BC4DE43C7B1CDE48

#include <type_traits>

namespace detail {
    template<bool COND, typename T>
    using CondConst_t = std::conditional_t<COND, std::add_const_t<T>, T>;
}

#endif //OBJECT_ARRAY_2_CONDCONST_A4E5523D399943E5BC4DE43C7B1CDE48
