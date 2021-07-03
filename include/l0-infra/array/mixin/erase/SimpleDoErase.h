//
// Created by Darwin Yuan on 2021/7/3.
//

#ifndef OBJECT_ARRAY_SIMPLEDOERASE_H
#define OBJECT_ARRAY_SIMPLEDOERASE_H

#include <l0-infra/array/detail/ConceptDef.h>
#include <l0-infra/array/concept/ContiguousArrayLikeDataHolder.h>

namespace mixin {
    template<__cOnCePt(ConstContiguousArrayLikeDataHolder) T>
    class SimpleDoErase : public T {
        using Self = T;

    public:
        using typename T::SizeType;
        using typename T::ObjectType;

        static constexpr auto MAX_SIZE = T::MAX_SIZE;
        static constexpr auto ORDERED = T::ORDERED;

    protected:
        using Self::Num;
        using Self::Elems;

        using typename T::Trait;

    private:
        auto ToObject(SizeType n) -> ObjectType&& {
            return std::move(Trait::ToObject(Elems()[n]));
        }

        auto MoveElems(SizeType pos) -> void {
            if constexpr (std::is_trivially_copyable_v<ObjectType>) {
                ::memmove(Elems() + pos, Elems() + pos + 1, sizeof(ObjectType) * (Num() - pos));
            } else {
                for(auto i=pos; i<Num(); i++) {
                    Trait::Emplace(Elems()[i], ToObject(i+1));
                }
            }
        }

    public:
        auto DoErase(SizeType i) -> void {
            if constexpr(ORDERED) {
                Trait::Destroy(Elems()[i]);
                if(i < (Num() - 1)) MoveElems(i);
            } else {
                if (i < Num()) Trait::Replace(Elems()[i], ToObject(Num()));
            }
            Trait::Destroy(Elems()[Num()]);
        }
    };
}

#endif //OBJECT_ARRAY_SIMPLEDOERASE_H
