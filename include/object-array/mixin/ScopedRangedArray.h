//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_SCOPEDRANGEDARRAY_H
#define OBJECT_ARRAY_SCOPEDRANGEDARRAY_H

#include <object-array/concept/ScopedArrayLike.h>
#include <object-array/mixin/detail/DefMixin.h>
#include <object-array/mixin/RangedArray.h>

namespace mixin {
    template<_concept::ConstScopedArrayLike T>
    class ScopedRangedArray : public detail::Extends<RangedArray<T>> {
        using Self = detail::Extends<RangedArray<T>>;
    public:
        using Self::GetScope;
    };
}

#endif //OBJECT_ARRAY_SCOPEDRANGEDARRAY_H
