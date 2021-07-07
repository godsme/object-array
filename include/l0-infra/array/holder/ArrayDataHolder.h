//
// Created by Darwin Yuan on 2021/6/21.
//

#ifndef OBJECT_ARRAY_ARRAYDATAHOLDER_H
#define OBJECT_ARRAY_ARRAYDATAHOLDER_H

#include <l0-infra/array/holder/detail/DeduceElemType.h>
#include <l0-infra/array/holder/detail/ObjectTrait.h>
#include <l0-infra/array/detail/ArrayScope.h>
#include <l0-infra/base/DeduceSizeType.h>
#include <l0-infra/base/BitSet.h>
#include <l0-infra/base/IntOpt.h>

namespace holder {
    template<typename OBJ, std::size_t MAX_NUM, bool ORDERED>
    struct ArrayDataHolder {
        using ObjectType = OBJ;
        using ElemType = std::decay_t<holder::ElemType<OBJ>>;
        using SizeType = DeduceSizeType_t<MAX_NUM>;
        using Trait = detail::ObjectTrait<ElemType, ObjectType>;
        constexpr static SizeType MAX_SIZE = MAX_NUM;
        constexpr static bool IS_CONST = std::is_const_v<OBJ>;
        constexpr static bool IS_ORDERED = ORDERED;

    protected:
        auto ClearContent(SizeType num) -> void {
            if constexpr (!std::is_trivially_destructible_v<ElemType>) {
                for (int i = 0; i < num; i++) Trait::Destroy(elems[i]);
            }
        }

        auto ConstructFrom(ElemType const*array, SizeType num) -> void {
            if constexpr (std::is_trivially_copyable_v<ElemType>) {
                ::memcpy(elems, array, sizeof(ElemType) * num);
            } else {
                for (auto i = 0; i < num; i++) {
                    Trait::Emplace(elems[i], Trait::ConstToObject(array[i]));
                }
            }
        }

        auto ConstructFrom(ElemType * array, SizeType num) -> void {
            if constexpr (std::is_trivially_copyable_v<ElemType>) {
                ::memcpy(elems, array, sizeof(ElemType) * num);
            } else {
                for (auto i = 0; i < num; i++) {
                    Trait::Emplace(elems[i], std::move(Trait::ToObject(array[i])));
                }
            }
        }

    protected:
        ArrayDataHolder() = default;

        ArrayDataHolder(std::initializer_list<OBJ> l) {
            SizeType i = 0;
            for (auto &&elem : l) {
                if (i == MAX_NUM) break;
                Trait::Emplace(elems[i++], std::move(elem));
            }
        }

        template<typename U>
        ArrayDataHolder(U *array, SizeType num) {
            ConstructFrom(array, num);
        }

        static auto ConstElemToObject(ElemType const& elem) -> ObjectType const& {
            return Trait::ConstToObject(elem);
        }

        static auto ElemToObject(ElemType& elem) -> ObjectType& {
            return Trait::ToObject(elem);
        }

    protected:
        ElemType elems[MAX_SIZE];
    };
}

#endif //OBJECT_ARRAY_ARRAYDATAHOLDER_H
