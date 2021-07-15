//
// Created by Darwin Yuan on 2021/7/9.
//

#ifndef OBJECT_ARRAY_2_RANGEDELEMCOUNT_16FFA903B72C449EBC7FA0265221FB96
#define OBJECT_ARRAY_2_RANGEDELEMCOUNT_16FFA903B72C449EBC7FA0265221FB96

namespace mixin {
    template<typename T>
    class RangedElemCount : public T {
        using Self = T;

    public:
        using typename T::SizeType;
        using typename T::ObjectType;
        using typename T::BitMap;

    public:
        auto GetNum() const -> SizeType {
            return Self::IndexEnd() - Self::IndexBegin();
        }

        auto Any() const -> bool {
            return Self::IndexBegin() < Self::IndexEnd();
        }

        auto GetOccupied() const -> BitMap {
            return BitMap(Self::IndexBegin(), Self::IndexEnd());
        }

        auto IsPresent(SizeType n) const -> bool {
            return n >= Self::IndexBegin() && n < Self::IndexEnd();
        }
    };
}

#endif //OBJECT_ARRAY_2_RANGEDELEMCOUNT_16FFA903B72C449EBC7FA0265221FB96
