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
    template<typename OBJ, std::size_t MAX_NUM>
    struct ArrayDataHolder {
        using ObjectType = OBJ;
        using ElemType = std::decay_t<holder::ElemType<OBJ>>;
        using SizeType = DeduceSizeType_t<MAX_NUM>;
        using Trait = detail::ObjectTrait<ElemType, ObjectType>;
        constexpr static SizeType MAX_SIZE = MAX_NUM;
        constexpr static bool IS_CONST = std::is_const_v<OBJ>;

    public:
        ArrayDataHolder() = default;

        //template<std::enable_if_t<std::is_same_v<NonConstElemType, decltype(NonConstElemType(std::declval<OBJ&&>()))>, int> = 0>
        template<typename ... ARGS>
        ArrayDataHolder(std::initializer_list<OBJ> l) {
            SizeType i = 0;
            for (auto &&elem : l) {
                if (i == MAX_NUM) break;
                Trait::Emplace(elems[i++], std::move(elem));
            }
        }

        template<typename U, std::enable_if_t<std::is_same_v<std::remove_const_t<U>, OBJ> ||
                                              std::is_same_v<std::remove_const_t<U>, ElemType>, int> = 0>
        ArrayDataHolder(U *array, SizeType num) {
            if constexpr (std::is_trivially_copyable_v<ElemType>) {
                ::memcpy(elems, array, sizeof(ElemType) * num);
            } else {
                for (auto i = 0; i < num; i++) {
                    Trait::Emplace(elems[i], std::move(Trait::ToObject(array[i])));
                }
            }
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
