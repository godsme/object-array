//
// Created by Darwin Yuan on 2021/7/12.
//

#ifndef OBJECT_ARRAY_2_077399B0F010441FBBA366C94DB59BB1
#define OBJECT_ARRAY_2_077399B0F010441FBBA366C94DB59BB1

namespace mixin {
    template<typename T>
    struct IndexedObjectAccessor : T {
        using typename T::SizeType;
        using typename T::ObjectType;

        auto GetObject(SizeType n) const -> ObjectType const& {
            return T::GetArray().GetObject(T::GetIndices()[n]);
        }

        auto GetObject(SizeType n) -> ObjectType& {
            return T::GetArray().GetObject(T::GetIndices()[n]);
        }
    };
}

#endif //OBJECT_ARRAY_2_077399B0F010441FBBA366C94DB59BB1
