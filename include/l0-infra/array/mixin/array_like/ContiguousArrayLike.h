//
// Created by Darwin Yuan on 2021/7/8.
//

#ifndef OBJECT_ARRAY_2_CONTIGUOUSARRAYLIKE_H
#define OBJECT_ARRAY_2_CONTIGUOUSARRAYLIKE_H

namespace mixin {
    template<typename T>
    struct ContiguousArrayLike : T {
        using typename T::SizeType;

    protected:
        using T::This;

    public:
        auto Num() -> SizeType& {
            return This()->num;
        }

        auto Num() const -> SizeType {
            return This()->num;
        }
    };
}

#endif //OBJECT_ARRAY_2_CONTIGUOUSARRAYLIKE_H
