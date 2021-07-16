//
// Created by Darwin Yuan on 2021/7/14.
//

#ifndef OBJECT_ARRAY_2_B3C98F1BFC9B4633B33A7AA998998ECE
#define OBJECT_ARRAY_2_B3C98F1BFC9B4633B33A7AA998998ECE

namespace mixin {
    template<typename T>
    struct RangeRotateExt : T {
        using typename T::SizeType;
        using typename T::OffsetType;

    protected:
        using typename T::ThisType;

        template<bool TO_LEFT>
        auto DoRangeRotate(OffsetType from, OffsetType until, SizeType n) -> void {
            auto num = T::GetNum();
            if(num == 0) return;

            SizeType from_ = from.ToIndex(T::GetNum());
            SizeType until_ = until.ToIndex(T::GetNum());
            if((from_ >= until_)) return;

            n %= num;

            SizeType to;

            if constexpr(TO_LEFT) {
                to = from_ + n;
                if(to >= until_) return;
            }  else {
                if(n >= until_) return;
                to = until_ - n;
                if(to <= from_) return;
            }

            T::Unsafe_RangeRotate(from_, to, until_);
        }

    public:
        auto Unsafe_RangeRotateLeft(SizeType from, SizeType until, SizeType n = 1) & -> ThisType & {
            T::Unsafe_RangeRotate(from, from + n, until);
            return T::ToThisType();
        }

        auto RangeRotateLeft(OffsetType from, OffsetType until, SizeType n = 1) & -> ThisType & {
            DoRangeRotate<true>(from, until, n);
            return T::ToThisType();
        }

        auto RotateLeftFrom(OffsetType from, SizeType n = 1) & -> ThisType & {
            return RangeRotateLeft(from, T::IndexEnd(), n);
        }

        auto RotateLeftUntil(OffsetType until, SizeType n = 1) & -> ThisType & {
            return RangeRotateLeft(T::IndexBegin(), until, n);
        }

        auto Unsafe_RotateLeftFrom(SizeType from, SizeType n = 1) & -> ThisType & {
            return Unsafe_RangeRotateLeft(from, from + n, T::IndexEnd());
        }

        auto Unsafe_RotateLeftUntil(SizeType until, SizeType n = 1) & -> ThisType & {
            return Unsafe_RangeRotateLeft(T::IndexBegin(), T::IndexBegin() + n, until);
        }

        auto Unsafe_RangeRotateRight(SizeType from, SizeType until, SizeType n = 1) & -> ThisType & {
            T::Unsafe_RangeRotate(from, until - n, until);
            return T::ToThisType();
        }

        auto RangeRotateRight(OffsetType from, OffsetType until, SizeType n = 1) & -> ThisType & {
            DoRangeRotate<false>(from, until, n);
            return T::ToThisType();
        }

        auto RotateRightFrom(OffsetType from, SizeType n = 1) & -> ThisType & {
            return RangeRotateRight(from, T::IndexEnd(), n);
        }

        auto RotateRightUntil(OffsetType until, SizeType n = 1) & -> ThisType & {
            return RangeRotateRight(T::IndexBegin(), until, n);
        }

        auto Unsafe_RotateRightFrom(SizeType from, SizeType n = 1) & -> ThisType & {
            return Unsafe_RangeRotateRight(from, from + n, T::IndexEnd());
        }

        auto Unsafe_RotateRightUntil(SizeType until, SizeType n = 1) & -> ThisType & {
            return Unsafe_RangeRotateRight(T::IndexBegin(), T::IndexBegin() + n, until);
        }

        auto Unsafe_RangeRotateLeft(SizeType from, SizeType until, SizeType n = 1) && = delete;
        auto Unsafe_RangeRotateRight(SizeType from, SizeType until, SizeType n = 1) && = delete;
        auto Unsafe_RotateLeftFrom(SizeType from, SizeType n = 1) && = delete;
        auto Unsafe_RotateRightFrom(SizeType from,SizeType n = 1) && = delete;
        auto Unsafe_RotateLeftUntil(SizeType until, SizeType n = 1) && = delete;
        auto Unsafe_RotateRightUntil(SizeType until,SizeType n = 1) && = delete;
        auto RangeRotateLeft(OffsetType from, OffsetType until, SizeType n = 1) && = delete;
        auto RotateLeftFrom(OffsetType from, SizeType n = 1) && = delete;
        auto RotateLeftUntil(OffsetType until, SizeType n = 1) && = delete;
        auto RangeRotateRight(OffsetType from, OffsetType until, SizeType n = 1) && = delete;
        auto RotateRightFrom(OffsetType from, SizeType n = 1) && = delete;
        auto RotateRightUntil(OffsetType until, SizeType n = 1) && = delete;
    };
}

#endif //OBJECT_ARRAY_2_B3C98F1BFC9B4633B33A7AA998998ECE
