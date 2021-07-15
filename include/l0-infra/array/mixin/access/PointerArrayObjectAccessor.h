//
// Created by Darwin Yuan on 2021/7/13.
//

#ifndef OBJECT_ARRAY_2_986E75A30FEC4350833C134180060B32
#define OBJECT_ARRAY_2_986E75A30FEC4350833C134180060B32

namespace mixin {
    template<typename T>
    struct PointerArrayObjectAccessor : T {
        using typename T::SizeType;
        using typename T::ObjectType;

        auto GetObject(SizeType n) const -> ObjectType const& {
            return *T::GetPointers()[n];
        }

        auto GetObject(SizeType n) -> ObjectType& {
            return *T::GetPointers()[n];
        }
    };
}

#endif //OBJECT_ARRAY_2_986E75A30FEC4350833C134180060B32
