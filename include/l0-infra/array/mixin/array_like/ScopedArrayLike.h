//
// Created by Darwin Yuan on 2021/7/11.
//

#ifndef OBJECT_ARRAY_2_B9DE2E49B09746968C06CF1E0A5B2DEA
#define OBJECT_ARRAY_2_B9DE2E49B09746968C06CF1E0A5B2DEA

namespace mixin {
    template<typename T>
    struct ScopedArrayLike : T {
        using typename T::BitMap;

    protected:
        using T::This;

    public:
        auto GetScope() const -> BitMap {
            return This()->scope;
        }

        auto GetScope() -> BitMap& {
            return (This()->scope);
        }
    };
}

#endif //OBJECT_ARRAY_2_B9DE2E49B09746968C06CF1E0A5B2DEA
