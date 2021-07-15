//
// Created by Darwin Yuan on 2021/7/12.
//

#ifndef OBJECT_ARRAY_2_4249685682FE49E999253C7414D0122B
#define OBJECT_ARRAY_2_4249685682FE49E999253C7414D0122B

namespace mixin {
    template<typename T>
    struct ElemCountExt : T {
        using typename T::SizeType;
        using typename T::BitMap;

    public:
        auto NumOfFree() const -> SizeType {
            return T::MAX_SIZE - T::GetNum();
        }

        auto HasEnoughSlots(SizeType num) const -> bool {
            return num <= NumOfFree();
        }

        auto None() const -> bool {
            return !T::Any();
        }

        auto All() const -> bool {
            return NumOfFree() == 0;
        }

        auto GetAvailable() const -> BitMap {
            return ~T::GetOccupied();
        }
    };
}

#endif //OBJECT_ARRAY_2_4249685682FE49E999253C7414D0122B
