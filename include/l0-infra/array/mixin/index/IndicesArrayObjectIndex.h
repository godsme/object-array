//
// Created by Darwin Yuan on 2021/7/13.
//

#ifndef OBJECT_ARRAY_2_F5489FB0008A4D15B9FB4F20DA4254B4
#define OBJECT_ARRAY_2_F5489FB0008A4D15B9FB4F20DA4254B4

namespace mixin {
    template<typename T>
    struct IndicesArrayObjectIndex : T {
        using typename T::ObjectType;
        using typename T::Maybe;

    public:
        auto ObjectToIndex(ObjectType const *obj) -> Maybe {
            auto index = T::GetArray().ObjectToIndex(obj);
            return index ? T::GetIndices().FindIndex(*index) : std::nullopt;
        }
    };
}

#endif //OBJECT_ARRAY_2_F5489FB0008A4D15B9FB4F20DA4254B4
