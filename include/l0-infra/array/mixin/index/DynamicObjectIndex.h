//
// Created by Darwin Yuan on 2021/7/13.
//

#ifndef OBJECT_ARRAY_2_78E39AC98E634B28B923F94109D61D3B
#define OBJECT_ARRAY_2_78E39AC98E634B28B923F94109D61D3B

namespace mixin {
    template<typename T>
    struct DynamicArrayObjectIndex : T {
        using typename T::ObjectType;
        using typename T::Maybe;

    public:
        auto ObjectToIndex(ObjectType const *obj) -> Maybe {
            return T::GetPointers().FindIndex(const_cast<ObjectType*>(obj));
        }
    };
}

#endif //OBJECT_ARRAY_2_78E39AC98E634B28B923F94109D61D3B
