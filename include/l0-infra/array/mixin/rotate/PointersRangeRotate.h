//
// Created by Darwin Yuan on 2021/7/14.
//

#ifndef OBJECT_ARRAY_2_8DB9991776FA4D54A5E1513230D012E6
#define OBJECT_ARRAY_2_8DB9991776FA4D54A5E1513230D012E6

namespace mixin {
    template<typename T>
    struct PointersRangeRotate : T {
        using typename T::SizeType;

    protected:
        using typename T::ThisType;

    public:
        auto Unsafe_RangeRotate(SizeType from, SizeType to, SizeType until) -> void {
            T::GetPointers().Unsafe_RangeRotate(from, to, until);
        }
    };
}

#endif //OBJECT_ARRAY_2_8DB9991776FA4D54A5E1513230D012E6
