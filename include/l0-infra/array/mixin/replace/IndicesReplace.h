//
// Created by Darwin Yuan on 2021/7/13.
//

#ifndef OBJECT_ARRAY_2_CC94C0D5EE11465BBA4B9E5F6E634CFB
#define OBJECT_ARRAY_2_CC94C0D5EE11465BBA4B9E5F6E634CFB

namespace mixin {
    template<typename T>
    struct IndicesReplace : T {
        using typename T::SizeType;
        using typename T::ObjectType;
        using typename T::Maybe;

    public:
        template<typename ... ARGS>
        auto Replace(SizeType i, ARGS&& ... args) -> ObjectType* {
            auto* index = T::GetIndices().At(i);
            if(index == nullptr) { return nullptr; }
            Maybe newIndex = T::GetArray().Replace_I(*index, std::forward<ARGS>(args)...);
            T::GetIndices().Replace(i, *newIndex);
            return newIndex.has_value() ? &T::GetArray().GetObject(*newIndex) : nullptr;
        }

        template<typename ... ARGS>
        auto Replace_I(SizeType i, ARGS&& ... args) -> Maybe {
            auto* index = T::GetIndices().At(i);
            if(index == nullptr) { return std::nullopt; }
            Maybe newIndex = T::GetArray().Replace_I(*index, std::forward<ARGS>(args)...);
            if(newIndex) T::GetIndices().Replace(i, *newIndex);
            return newIndex;
        }
    };
}

#endif //OBJECT_ARRAY_2_CC94C0D5EE11465BBA4B9E5F6E634CFB
