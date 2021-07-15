//
// Created by Darwin Yuan on 2021/7/12.
//

#ifndef OBJECT_ARRAY_2_B26C638F02C640F98C5A4BA2890F554E
#define OBJECT_ARRAY_2_B26C638F02C640F98C5A4BA2890F554E

namespace mixin {
    template<typename T>
    struct ArrayElemCount : T {
        using typename T::SizeType;
        using typename T::BitMap;

    public:
        auto GetNum() const -> SizeType {
            return T::Num();
        }

        auto Any() const -> bool {
            return T::Num() > 0;
        }

        auto GetOccupied() const -> BitMap {
            return BitMap(0, T::Num());
        }

        auto IsPresent(SizeType n) const -> bool {
            return n < T::Num();
        }
    };
}

#endif //OBJECT_ARRAY_2_B26C638F02C640F98C5A4BA2890F554E
