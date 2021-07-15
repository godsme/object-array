//
// Created by Darwin Yuan on 2021/7/10.
//

#ifndef OBJECT_ARRAY_2_111D22B7268B4AFE97F5D825690469D2
#define OBJECT_ARRAY_2_111D22B7268B4AFE97F5D825690469D2

#include <l0-infra/array/concept/Less.h>

namespace mixin {
    template<typename T>
    struct IndicesLess : T {
        using typename T::ObjectType;

    public:
        template<__lEsS_cOnCePt(LESS)>
        auto GetIndicesLess(LESS&& less) const -> auto {
            return [&less, &array = T::GetArray()](auto l, auto r) -> bool {
                return less(array.GetObject(l), array.GetObject(r));
            };
        }
    };
}

#endif //OBJECT_ARRAY_2_111D22B7268B4AFE97F5D825690469D2
