//
// Created by Darwin Yuan on 2021/7/11.
//

#ifndef OBJECT_ARRAY_2_80EB7347DB124C6895D3506F3B8640EF
#define OBJECT_ARRAY_2_80EB7347DB124C6895D3506F3B8640EF

namespace mixin {
    template<typename T>
    struct ScopedElemCount : T {
        using typename T::SizeType;
        using typename T::ObjectType;
        using typename T::BitMap;

    public:
        auto GetNum() const -> SizeType {
            return T::GetScope().count();
        }

        auto Any() const -> bool {
            return T::GetScope().any();
        }

        auto None() const -> bool {
            return T::GetScope().none();
        }

        auto GetOccupied() const -> BitMap {
            return T::GetScope();
        }

        auto IsPresent(SizeType n) const -> bool {
            return T::GetScope().test(n);
        }
    };
}

#endif //OBJECT_ARRAY_2_80EB7347DB124C6895D3506F3B8640EF
