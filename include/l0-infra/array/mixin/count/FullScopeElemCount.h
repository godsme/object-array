//
// Created by Darwin Yuan on 2021/7/15.
//

#ifndef OBJECT_ARRAY_6AEE23B6560849BB96E3982C9E9B677F
#define OBJECT_ARRAY_6AEE23B6560849BB96E3982C9E9B677F

namespace mixin {
    template<typename T>
    struct FullScopedElemCount : T {
        using typename T::BitMap;
        using typename T::SizeType;

    protected:
        using T::GetScope;

    public:
        auto All() const -> bool {
            return GetScope().all();
        }

        auto GetAvailable() const -> BitMap {
            return ~GetScope();
        }

        auto NumOfFree() const -> SizeType {
            return GetAvailable().count();
        }

        auto HasEnoughSlots(SizeType num) const -> bool {
            return num <= NumOfFree();
        }
    };
}

#endif //OBJECT_ARRAY_6AEE23B6560849BB96E3982C9E9B677F
