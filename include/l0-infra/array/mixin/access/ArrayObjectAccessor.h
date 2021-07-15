//
// Created by Darwin Yuan on 2021/7/11.
//

#ifndef OBJECT_ARRAY_2_1860A0CBB6C649CFABE66E6D7D2554F6
#define OBJECT_ARRAY_2_1860A0CBB6C649CFABE66E6D7D2554F6

namespace mixin {
    template<typename T>
    struct ArrayObjectAccessor : T {
        using typename T::SizeType;
        using typename T::ObjectType;

    public:
        auto GetObject(SizeType n) const -> ObjectType const& {
            return T::GetArray().GetObject(n);
        }
        auto GetObject(SizeType n) -> ObjectType& {
            return T::GetArray().GetObject(n);
        }
    };
}

#endif //OBJECT_ARRAY_2_1860A0CBB6C649CFABE66E6D7D2554F6
