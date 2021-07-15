//
// Created by Darwin Yuan on 2021/7/12.
//

#ifndef OBJECT_ARRAY_2_DAE9148249874399935F070E4280C52F
#define OBJECT_ARRAY_2_DAE9148249874399935F070E4280C52F

namespace mixin {
    template<typename T>
    struct IndicesRangeScopeInit : T {
        auto InitIndices() -> void {
            T::GetIndices().Init(T::GetArray(), T::GetArray().GetScope());
        }
    };
}

#endif //OBJECT_ARRAY_2_DAE9148249874399935F070E4280C52F
