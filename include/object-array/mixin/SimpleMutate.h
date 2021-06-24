//
// Created by Darwin Yuan on 2021/6/24.
//

#ifndef OBJECT_ARRAY_SIMPLEMUTATE_H
#define OBJECT_ARRAY_SIMPLEMUTATE_H

#include <object-array/concept/ContinuousArrayLikeDataHolder.h>

namespace mixin {
    template<_concept::ContinuousArrayLikeDataHolder T>
    class SimpleMutate : public T {
        using Self = T;

    public:
        using typename T::SizeType;
        using typename T::ObjectType;
        using typename T::Trait;

        static constexpr auto MAX_SIZE = T::MAX_SIZE;

    public:
        using Self::GetObj;
        using Self::Num;
        using Self::Elems;

    private:
        auto DoErase(SizeType i) -> void {
            --Num();
            if (i < Num()) Trait::Replace(Elems()[i], std::move(GetObj(Num())));
            Trait::Destroy(Elems()[Num()]);
        }

    public:
        template<typename ... ARGS>
        auto Append(ARGS &&... args) -> ObjectType * {
            if (Num() >= MAX_SIZE) return nullptr;
            return Trait::Emplace(Elems()[Num()++], std::forward<ARGS>(args)...);
        }

        template<typename ... ARGS>
        auto Replace(SizeType i, ARGS &&... args) -> ObjectType * {
            if (i >= Num()) return nullptr;
            return Trait::Replace(Elems()[i], std::forward<ARGS>(args)...);
        }

        auto Erase(SizeType i) -> void {
            if (i < Num()) DoErase(i);
        }

        template<typename PRED>
        auto CleanUpBy(PRED&& pred) -> void {
            if(Num() == 0) return;
            for(int i = Num() - 1; i >=0; --i) {
                if(pred(GetObj(i))) DoErase(i);
            }
        }
    };
}

#endif //OBJECT_ARRAY_SIMPLEMUTATE_H
