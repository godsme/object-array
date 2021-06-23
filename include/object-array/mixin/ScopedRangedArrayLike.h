//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_SCOPEDRANGEDARRAYLIKE_H
#define OBJECT_ARRAY_SCOPEDRANGEDARRAYLIKE_H

#include <object-array/concept/ScopedArrayLike.h>
#include <object-array/mixin/RangedArrayLike.h>
#include <object-array/mixin/detail/DefMixin.h>

namespace mixin {
    template<_concept::SimpleScopedRangedArrayLike T>
    class ScopedRangedArrayLike : public detail::Extends<RangedArrayLike<T>> {
        using Self = detail::Extends<RangedArrayLike<T>>;
    public:
        using Self::GetScope;
    };
}

#endif //OBJECT_ARRAY_SCOPEDRANGEDARRAYLIKE_H
