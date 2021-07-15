//
// Created by Darwin Yuan on 2021/7/8.
//

#ifndef OBJECT_ARRAY_2_OBJECTARRAYHOLDER_H
#define OBJECT_ARRAY_2_OBJECTARRAYHOLDER_H

#include <l0-infra/array/holder/detail/ObjectArrayHolder.h>
#include <l0-infra/array/holder/detail/Holder.h>

namespace holder::detail {
    template<typename OBJ, std::size_t MAX_NUM>
    using UnOrderedObjectArrayHolder = ObjectArrayHolder<OBJ, MAX_NUM, false>;
}

namespace holder {
    template<typename OBJ, std::size_t MAX_NUM>
    using ObjectArrayHolder = holder::detail::Holder<OBJ, MAX_NUM, holder::detail::UnOrderedObjectArrayHolder>;
}

#endif //OBJECT_ARRAY_2_OBJECTARRAYHOLDER_H
