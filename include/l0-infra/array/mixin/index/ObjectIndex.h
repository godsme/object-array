//
// Created by Darwin Yuan on 2021/7/9.
//

#ifndef OBJECT_ARRAY_2_OBJECTINDEX_BEC9A7EE9E1A480C885C99DAFC290C47
#define OBJECT_ARRAY_2_OBJECTINDEX_BEC9A7EE9E1A480C885C99DAFC290C47

namespace mixin {
    template<typename T>
    struct ObjectIndex : T {
        using typename T::ObjectType;
        using typename T::Maybe;

    public:
        auto ObjectToIndex(ObjectType const *obj) -> Maybe {
            auto *base = &T::GetObject(0);
            return obj < base ? std::nullopt : Maybe(obj - base);
        }
    };
}

#endif //OBJECT_ARRAY_2_OBJECTINDEX_BEC9A7EE9E1A480C885C99DAFC290C47
