//
// Created by Darwin Yuan on 2021/7/14.
//

#ifndef OBJECT_ARRAY_2_2872B2B6A4B24141845E6EEB90E6DDB9
#define OBJECT_ARRAY_2_2872B2B6A4B24141845E6EEB90E6DDB9

namespace mixin {
    template<typename T>
    struct Rotate : T {
        using typename T::SizeType;
        using typename T::OffsetType;

    protected:
        using typename T::ThisType;

    public:
        auto Unsafe_RotateLeft(SizeType n = 1) & -> decltype(auto) {
            return T::Unsafe_RangeRotateLeft(T::IndexBegin(), T::IndexEnd(), n);
        }

        auto RotateLeft(SizeType n = 1) & -> decltype(auto) {
            auto num = T::GetNum();
            return num == 0 ? T::ToThisType() : Unsafe_RotateLeft(n % num);
        }

        auto Unsafe_RotateRight(SizeType n = 1) & -> decltype(auto) {
            return T::Unsafe_RangeRotateRight(T::IndexBegin(), T::IndexEnd(), n);
        }

        auto RotateRight(SizeType n = 1) & -> decltype(auto) {
            auto num = T::GetNum();
            return num == 0 ? T::ToThisType() : Unsafe_RotateRight(n % num);
        }

        auto Unsafe_RotateLeft(SizeType = 1) && = delete;
        auto Unsafe_RotateRight(SizeType = 1) && = delete;
        auto RotateLeft(SizeType = 1) && = delete;
        auto RotateRight(SizeType = 1) && = delete;
    };
}

#endif //OBJECT_ARRAY_2_2872B2B6A4B24141845E6EEB90E6DDB9
