//
// Created by Darwin Yuan on 2021/7/10.
//

#ifndef OBJECT_ARRAY_2_6A18B18FAAB24A489743395E4BAA14C9
#define OBJECT_ARRAY_2_6A18B18FAAB24A489743395E4BAA14C9

namespace mixin {
    template<typename T>
    struct IndicesRangeInit : T {
        auto InitIndices() -> void {
            T::GetIndices().Init(T::GetArray());
        }
    };
}

#endif //OBJECT_ARRAY_2_6A18B18FAAB24A489743395E4BAA14C9
