//
// Created by Darwin Yuan on 2021/7/14.
//

#ifndef OBJECT_ARRAY_2_E30EFEB8C5794170BC50EE363CA4D3B7
#define OBJECT_ARRAY_2_E30EFEB8C5794170BC50EE363CA4D3B7

#include <algorithm>

namespace mixin {
    template<typename T>
    struct ArrayRangeRotate : T {
        using typename T::SizeType;

    protected:
        using typename T::ThisType;

    public:
        auto Unsafe_RangeRotate(SizeType from, SizeType to, SizeType until) -> void {
            std::rotate(&T::GetObject(from), &T::GetObject(to), &T::GetObject(until));
        }
    };
}

#endif //OBJECT_ARRAY_2_E30EFEB8C5794170BC50EE363CA4D3B7
