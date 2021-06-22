//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_ARRAYDATAHOLDERCONCEPT_H
#define OBJECT_ARRAY_ARRAYDATAHOLDERCONCEPT_H

namespace holder::detail {
    template<typename DATA_HOLDER>
    class ArrayDataHolderConcept {
        auto This() const -> DATA_HOLDER const * {
            return reinterpret_cast<DATA_HOLDER const*>(this);
        }
    public:
        using ElemType = typename DATA_HOLDER::ElemType;
        using ObjectType = typename DATA_HOLDER::ObjectType;

        auto Elems() const -> decltype(auto) {
            return (This()->Elems());
        }

        auto Num() const -> decltype(auto) {
            return (This()->Num());
        }

        static auto ElemToObject(ElemType const& elem) -> ObjectType const& {
            return DATA_HOLDER::ElemToObject(elem);
        }
    };
}

#endif //OBJECT_ARRAY_ARRAYDATAHOLDERCONCEPT_H
