//
// Created by Darwin Yuan on 2021/7/14.
//

#ifndef OBJECT_ARRAY_2_7BD829C758AA4CA7954D0D924198394F
#define OBJECT_ARRAY_2_7BD829C758AA4CA7954D0D924198394F


namespace mixin {
    template<typename T>
    struct IndicesRangeRotate : T {
        using typename T::SizeType;

    protected:
        using typename T::ThisType;

    public:
        auto Unsafe_RangeRotate(SizeType from, SizeType to, SizeType until) -> void {
            T::GetIndices().Unsafe_RangeRotate(from, to, until);
        }
    };
}

#endif //OBJECT_ARRAY_2_7BD829C758AA4CA7954D0D924198394F
