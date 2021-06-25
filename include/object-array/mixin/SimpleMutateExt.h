//
// Created by Darwin Yuan on 2021/6/24.
//

#ifndef OBJECT_ARRAY_SIMPLEMUTATEEXT_H
#define OBJECT_ARRAY_SIMPLEMUTATEEXT_H

namespace mixin {
    template<_concept::ContinuousArrayLikeDataHolder T>
    class SimpleMutateExt : public SimpleMutate<T> {
        using Self = SimpleMutate<T>;
    public:
        using typename Self::ObjectType;
        using typename Self::SizeType;
        using typename Self::BitMap;
        using typename Self::Maybe;

    public:
        using Self::GetObj;

        using Self::Replace;
        using Self::Erase;

    private:
        auto GetObjIndex(ObjectType const* obj) -> Maybe {
            auto* base = &GetObj(0);
            return obj < base ? std::nullopt : Maybe(obj - base);
        }

    public:
        template<typename ... ARGS>
        auto ReplaceObj(ObjectType const& obj, ARGS &&... args) -> ObjectType * {
            auto index = GetObjIndex(&obj);
            return index ? Replace(*index, std::forward<ARGS>(args)...) : nullptr;
        }

        auto Remove(ObjectType *p) -> void {
            auto index = GetObjIndex(p);
            if (index) Erase(*index);
        }
    };
}

#endif //OBJECT_ARRAY_SIMPLEMUTATEEXT_H
