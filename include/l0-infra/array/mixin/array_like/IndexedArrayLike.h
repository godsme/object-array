//
// Created by Darwin Yuan on 2021/7/9.
//

#ifndef OBJECT_ARRAY_2_INDEXEDARRAYLIKE_DBD6DF6D92C1472A9AFBDB611AF95B25
#define OBJECT_ARRAY_2_INDEXEDARRAYLIKE_DBD6DF6D92C1472A9AFBDB611AF95B25

namespace mixin {
    template<typename T>
    struct IndexedArrayLike : T {
    protected:
        using T::This;

    public:
        using typename T::SizeType;
        using typename T::ObjectType;

        using T::GetArray;

    public:
        auto Num() const -> SizeType {
            return This()->GetIndices().GetNum();
        }

        auto GetIndices() const -> decltype(auto) {
            return This()->GetIndices();
        }

        auto GetIndices() -> decltype(auto) {
            return This()->GetIndices();
        }
    };
}

#endif //OBJECT_ARRAY_2_INDEXEDARRAYLIKE_DBD6DF6D92C1472A9AFBDB611AF95B25
