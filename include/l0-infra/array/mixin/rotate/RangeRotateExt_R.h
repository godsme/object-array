//
// Created by Darwin Yuan on 2021/7/14.
//

#ifndef OBJECT_ARRAY_2_F5194FF2167040FCA99ECF1EA4388E91
#define OBJECT_ARRAY_2_F5194FF2167040FCA99ECF1EA4388E91

namespace mixin {
    template<typename T>
    struct RangeRotateExt_R : T {
        using typename T::SizeType;
        using typename T::OffsetType;

    protected:
        using typename T::ThisType;

    public:
        using T::Unsafe_RangeRotateLeft;
        auto Unsafe_RangeRotateLeft(SizeType from, SizeType until, SizeType n = 1) && -> ThisType {
            return T::Unsafe_RangeRotateLeft(from, until, n);
        }

        using T::RangeRotateLeft;
        auto RangeRotateLeft(OffsetType from, OffsetType until, SizeType n = 1) && -> ThisType {
            return T::RangeRotateLeft(from, until, n);
        }

        using T::RotateLeftFrom;
        auto RotateLeftFrom(OffsetType from, SizeType n = 1) && -> auto {
            return T::RotateLeftFrom(from, n);
        }

        using T::RotateLeftUntil;
        auto RotateLeftUntil(OffsetType until, SizeType n = 1) && -> auto {
            return T::RangeRotateLeft(until, n);
        }

        using T::Unsafe_RotateLeftFrom;
        auto Unsafe_RotateLeftFrom(SizeType from, SizeType n = 1) && -> auto {
            return T::Unsafe_RotateLeftFrom(from, n);
        }

        using T::Unsafe_RotateLeftUntil;
        auto Unsafe_RotateLeftUntil(SizeType until, SizeType n = 1) && -> auto {
            return T::Unsafe_RotateLeftUntil(until, n);
        }

        using T::Unsafe_RangeRotateRight;
        auto Unsafe_RangeRotateRight(SizeType from, SizeType until, SizeType n = 1) && -> auto {
            return T::Unsafe_RangeRotateRight(from, until, n);
        }

        using T::RangeRotateRight;
        auto RangeRotateRight(OffsetType from, OffsetType until, SizeType n = 1) && -> auto {
            return T::RangeRotateRight(from, until, n);
        }

        using T::RotateRightFrom;
        auto RotateRightFrom(OffsetType from, SizeType n = 1) && -> auto {
            return T::RotateRightFrom(from, n);
        }

        using T::RotateRightUntil;
        auto RotateRightUntil(OffsetType until, SizeType n = 1) && -> auto {
            return T::RotateRightUntil(until, n);
        }

        using T::Unsafe_RotateRightFrom;
        auto Unsafe_RotateRightFrom(SizeType from, SizeType n = 1) && -> auto {
            return T::Unsafe_RotateRightFrom(from, n);
        }

        using T::Unsafe_RotateRightUntil;
        auto Unsafe_RotateRightUntil(SizeType until, SizeType n = 1) && -> auto {
            return T::Unsafe_RotateRightUntil(until, n);
        }
    };
}

#endif //OBJECT_ARRAY_2_F5194FF2167040FCA99ECF1EA4388E91
