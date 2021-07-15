//
// Created by Darwin Yuan on 2021/7/12.
//

#ifndef OBJECT_ARRAY_2_318A659349F948309BB6B4271A69BBAE
#define OBJECT_ARRAY_2_318A659349F948309BB6B4271A69BBAE

#include <string>

namespace mixin {
    template<typename T>
    struct OrderedErase : T {
        using typename T::SizeType;
        using typename T::ObjectType;

        static constexpr auto MAX_SIZE = T::MAX_SIZE;

    protected:
        using T::Num;
        using T::Elems;

    private:
        auto MoveElems(SizeType pos) -> void {
            if constexpr (std::is_trivially_copyable_v<ObjectType>) {
                ::memmove(Elems() + pos, Elems() + pos + 1, sizeof(ObjectType) * (Num() - pos));
            } else {
                for(auto i=pos; i<Num(); i++) {
                    T::MoveObject(i, 1 + i);
                }
                T::Destroy(Num());
            }
        }

        auto DoErase(SizeType i) -> void {
            --Num();
            T::Destroy(i);
            if(i < Num()) MoveElems(i);
        }

    public:
        auto Erase(SizeType i) -> void {
            if(i < Num()) DoErase(i);
        }
    };
}

#endif //OBJECT_ARRAY_2_318A659349F948309BB6B4271A69BBAE
