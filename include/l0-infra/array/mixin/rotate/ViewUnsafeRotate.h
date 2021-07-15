//
// Created by Darwin Yuan on 2021/7/14.
//

#ifndef OBJECT_ARRAY_2_954F063131CC49488D5B7A6985E66A60
#define OBJECT_ARRAY_2_954F063131CC49488D5B7A6985E66A60

namespace mixin {
    template<typename T>
    struct ViewUnsafeRotate : T {
        using typename T::SizeType;

    protected:
        using typename T::ThisType;

    public:
        auto Unsafe_RangeRotateLeft(SizeType from, SizeType until, SizeType n = 1) -> ThisType & {
            T::GetArray().Unsafe_RangeRotateLeft(from, until, n);
            return T::ToThisType();
        }

        auto Unsafe_RangeRotateRight(SizeType from, SizeType until, SizeType n = 1) -> ThisType & {
            T::GetArray().Unsafe_RangeRotateRight(from, until, n);
            return T::ToThisType();
        }
    };
}

#endif //OBJECT_ARRAY_2_954F063131CC49488D5B7A6985E66A60
