//
// Created by Darwin Yuan on 2021/7/15.
//

#ifndef OBJECT_ARRAY_2_491EF9E02C5F4CB7817202F8F4C59F57
#define OBJECT_ARRAY_2_491EF9E02C5F4CB7817202F8F4C59F57

namespace mixin {
    template<typename T>
    struct ArrayScopeMask : T {
        using typename T::BitMap;

        auto MaskScope(BitMap scope) const -> BitMap {
            return scope.Mask(T::IndexBegin(), T::IndexEnd());
        }
    };
}

#endif //OBJECT_ARRAY_2_491EF9E02C5F4CB7817202F8F4C59F57
