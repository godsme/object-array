//
// Created by Darwin Yuan on 2021/7/14.
//

#ifndef OBJECT_ARRAY_2_B08B3E2F8FFB48B28B66ABBF86D168F7
#define OBJECT_ARRAY_2_B08B3E2F8FFB48B28B66ABBF86D168F7

namespace mixin {
    template<typename T>
    struct Rotate_R : T {
        using typename T::SizeType;
        using typename T::OffsetType;

    protected:
        using typename T::ThisType;

    public:
        using T::Unsafe_RotateLeft;
        auto Unsafe_RotateLeft(SizeType n = 1) && -> auto {
            return T::Unsafe_RotateLeft(n);
        }

        using T::RotateLeft;
        auto RotateLeft(SizeType n = 1) && -> auto {
            return T::RotateLeft(n);
        }

        using T::Unsafe_RotateRight;
        auto Unsafe_RotateRight(SizeType n = 1) && -> auto {
            return T::Unsafe_RotateRight(n);
        }

        using T::RotateRight;
        auto RotateRight(SizeType n = 1) && -> auto {
            return T::RotateRight(n);
        }
    };
}

#endif //OBJECT_ARRAY_2_B08B3E2F8FFB48B28B66ABBF86D168F7
