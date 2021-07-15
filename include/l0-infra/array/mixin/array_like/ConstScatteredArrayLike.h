//
// Created by Darwin Yuan on 2021/7/9.
//

#ifndef OBJECT_ARRAY_2_CONSTSCATTEREDARRAYLIKE_H
#define OBJECT_ARRAY_2_CONSTSCATTEREDARRAYLIKE_H

namespace mixin {
    template<typename T>
    struct ConstScatteredArrayLike : T {
    protected:
        using T::This;

    public:
        using typename T::SizeType;
        using typename T::BitMap;

        auto IndexBegin() const -> SizeType {
            return 0;
        }

        auto IndexEnd() const -> SizeType {
            return T::MAX_SIZE;
        }

        auto GetScope() const -> BitMap { return This()->occupied; }
        auto GetScope() -> BitMap& { return This()->occupied; }
    };
}

#endif //OBJECT_ARRAY_2_CONSTSCATTEREDARRAYLIKE_H
