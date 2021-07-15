//
// Created by Darwin Yuan on 2021/7/12.
//

#ifndef OBJECT_ARRAY_2_07FA12CF3AA44180A226938E6851531C
#define OBJECT_ARRAY_2_07FA12CF3AA44180A226938E6851531C

#include <l0-infra/array/iterator/detail/ScopeIterator.h>
#include <l0-infra/array/iterator/detail/ViewIterator.h>

namespace iterator {
    template<typename ARRAY, typename OBJ_TYPE, typename SIZE_TYPE, typename BIT_MAP>
    using ScopeIterator = detail::ScopeIterator<ViewIterator<ARRAY, OBJ_TYPE, SIZE_TYPE>, BIT_MAP>;
}

#endif //OBJECT_ARRAY_2_07FA12CF3AA44180A226938E6851531C
