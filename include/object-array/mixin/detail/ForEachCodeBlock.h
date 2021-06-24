//
// Created by Darwin Yuan on 2021/6/24.
//

#ifndef OBJECT_ARRAY_FOREACHCODEBLOCK_H
#define OBJECT_ARRAY_FOREACHCODEBLOCK_H

#include <type_traits>

////////////////////////////////////////////////////////////////////////////////////////
#define __vIsIt_ReSuLt_TyPe \
std::decay_t<decltype(this->template Visit<TO_NON_CONST>(std::declval<OP&&>(), std::declval<SizeType>()))>

////////////////////////////////////////////////////////////////////////////////////////
#define __vIsIt_CoDe_BlOcK__ \
if constexpr(std::is_same_v<bool, __vIsIt_ReSuLt_TyPe>) { \
    if(auto r = Self::template Visit<TO_NON_CONST>(std::forward<OP>(op), i); !r) return r; \
} else if constexpr(std::is_convertible_v<std::size_t, __vIsIt_ReSuLt_TyPe>) { \
    if(auto r = Self::template Visit<TO_NON_CONST>(std::forward<OP>(op), i); r != 0) return r; \
} else  { \
    Self::template Visit<TO_NON_CONST>(std::forward<OP>(op), i); \
}

////////////////////////////////////////////////////////////////////////////////////////
#define __fOrEaCh_SuCcEsS_rEtUrN__ \
if constexpr(std::is_same_v<bool, __vIsIt_ReSuLt_TyPe>) { \
    return true; \
} else if constexpr(std::is_convertible_v<std::size_t, __vIsIt_ReSuLt_TyPe>) { \
    return __vIsIt_ReSuLt_TyPe{}; \
} else {}

#endif //OBJECT_ARRAY_FOREACHCODEBLOCK_H
