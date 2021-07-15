//
// Created by Darwin Yuan on 2021/7/13.
//

#ifndef OBJECT_ARRAY_2_E4CAFE6466474E6EB245F7B47843BF02
#define OBJECT_ARRAY_2_E4CAFE6466474E6EB245F7B47843BF02

namespace mixin {
    template<typename T>
    struct ViewObjectEquality : T {
        using typename T::ObjectType;

    public:
        auto GetEq() const -> decltype(auto) {
            return T::GetArray().GetEq();
        }
    };
}

#endif //OBJECT_ARRAY_2_E4CAFE6466474E6EB245F7B47843BF02
