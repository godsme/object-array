//
// Created by Darwin Yuan on 2021/6/24.
//

#ifndef OBJECT_ARRAY_SIMPLEMUTATE_H
#define OBJECT_ARRAY_SIMPLEMUTATE_H

#include <l0-infra/array/concept/ContinuousArrayLikeDataHolder.h>

namespace mixin {
    template<__cOnCePt(ContinuousArrayLikeDataHolder) T>
    class SimpleMutate : public T {
        using Self = T;

    public:
        using typename T::SizeType;
        using typename T::ObjectType;

        static constexpr auto MAX_SIZE = T::MAX_SIZE;

    protected:
        using Self::GetObj;
        using Self::Num;
        using Self::Elems;

        using typename T::Trait;

    private:
        auto DoErase(SizeType i) -> void {
            --Num();
            if (i < Num()) Trait::Replace(Elems()[i], std::move(GetObj(Num())));
            Trait::Destroy(Elems()[Num()]);
        }

    public:
        template<typename ... ARGS>
        auto Append(ARGS &&... args) -> ObjectType * {
            return Num() < MAX_SIZE ? Trait::Emplace(Elems()[Num()++], std::forward<ARGS>(args)...) : nullptr;
        }

        template<typename ... ARGS>
        auto Replace(SizeType i, ARGS &&... args) -> ObjectType * {
            return i < Num() ? Trait::Replace(Elems()[i], std::forward<ARGS>(args)...) : nullptr;
        }

        auto Erase(SizeType i) -> void {
            if (i < Num()) DoErase(i);
        }
    };
}

#endif //OBJECT_ARRAY_SIMPLEMUTATE_H
