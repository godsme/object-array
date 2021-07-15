//
// Created by Darwin Yuan on 2021/7/8.
//

#ifndef OBJECT_ARRAY_2_CONSTARRAYLIKE_H
#define OBJECT_ARRAY_2_CONSTARRAYLIKE_H

namespace mixin {
    template<typename T>
    struct ConstArrayLike : T {
        using T::This;

        using typename T::DataHolder;
        using ElemType = typename DataHolder::ElemType;
        using typename T::ObjectType;
        using typename T::SizeType;

        auto Elems() const -> ElemType const * {
            return This()->elems;
        }

        auto Elems() -> ElemType* {
            return This()->elems;
        }

        auto GetObject(SizeType n) -> ObjectType& {
            return DataHolder::ElemToObject(Elems()[n]);
        }

        auto GetObject(SizeType n) const -> ObjectType const& {
            return DataHolder::ConstElemToObject(Elems()[n]);
        }
    };
}

#endif //OBJECT_ARRAY_2_CONSTARRAYLIKE_H
