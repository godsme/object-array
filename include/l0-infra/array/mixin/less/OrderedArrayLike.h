//
// Created by Darwin Yuan on 2021/7/12.
//

#ifndef OBJECT_ARRAY_2_EC4E47EAB3D540CA8DB7533C4FD1D131
#define OBJECT_ARRAY_2_EC4E47EAB3D540CA8DB7533C4FD1D131

namespace mixin {
    template<typename T>
    struct OrderedArrayLike : T {

        auto GetLess() const -> decltype(auto) {
            return T::This()->GetObjectLess();
        }

        auto GetLess() -> decltype(auto) {
            return T::This()->GetObjectLess();
        }
    };
}

#endif //OBJECT_ARRAY_2_EC4E47EAB3D540CA8DB7533C4FD1D131
