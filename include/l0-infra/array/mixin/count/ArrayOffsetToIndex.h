//
// Created by Darwin Yuan on 2021/7/15.
//

#ifndef OBJECT_ARRAY_2_8C1710A422174110B63E07F1AE110D1C
#define OBJECT_ARRAY_2_8C1710A422174110B63E07F1AE110D1C

namespace mixin {
    template<typename T>
    struct ArrayOffsetToIndex : T {
        using typename T::OffsetType;

        auto OffsetToIndex(OffsetType offset) const -> typename T::SizeType {
            return offset.ToIndex(T::Num());
        }
    };
}

#endif //OBJECT_ARRAY_2_8C1710A422174110B63E07F1AE110D1C
