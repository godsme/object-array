//
// Created by Darwin Yuan on 2021/7/12.
//

#ifndef OBJECT_ARRAY_2_81E469FC27FD411C8942FC9F2FFA08BC
#define OBJECT_ARRAY_2_81E469FC27FD411C8942FC9F2FFA08BC

#include <l0-infra/array/iterator/detail/ScopeIterator.h>
#include <l0-infra/array/iterator/detail/WithIndexIterator.h>

namespace iterator {
    template<typename ARRAY, typename BIT_MAP, typename OBJ_TYPE>
    using WithIndexScopeIterator = detail::ScopeIterator<detail::ByIndexWithIndexIterator<ARRAY, OBJ_TYPE>, BIT_MAP>;
}

#endif //OBJECT_ARRAY_2_81E469FC27FD411C8942FC9F2FFA08BC
