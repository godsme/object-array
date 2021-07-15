//
// Created by Darwin Yuan on 2021/7/8.
//

#ifndef OBJECT_ARRAY_2_ARRAYHOLDER_H
#define OBJECT_ARRAY_2_ARRAYHOLDER_H

#include <l0-infra/base/Placement.h>
#include <l0-infra/base/detail/DeduceIntOptional.h>
#include <l0-infra/array/mixin/array_like/ArrayLike.h>
#include <l0-infra/array/mixin/array_like/ConstArrayLike.h>

namespace holder::detail {
    template<typename OBJ, std::size_t MAX_NUM, bool ORDERED = false>
    struct ArrayHolder {
        static_assert(!std::is_reference_v<OBJ>);

        using ObjectType = OBJ;
        using ElemType = Placement<std::remove_const_t<OBJ>>;
        using SizeType = ::detail::DeduceIntOptSizeType_t<MAX_NUM>;
        using Maybe    = IntOpt<SizeType>;

        constexpr static SizeType MAX_SIZE = MAX_NUM;
        constexpr static bool IS_CONST = std::is_const_v<OBJ>;
        constexpr static bool IS_ORDERED = ORDERED;

        // To avoid unnecessary zero-initialization, DO NOT CHANGE IT TO `=default`.
        ArrayHolder() {}
        ArrayHolder(std::initializer_list<OBJ> l) {
            SizeType i = 0;
            for (auto &&elem : l) {
                if (i == MAX_NUM) return;
                elems[i++].Emplace(std::move(elem));
            }
        }

    private:
        static auto ConstElemToObject(ElemType const &elem) -> ObjectType const & {
            return *elem;
        }

        static auto ElemToObject(ElemType& elem) -> ObjectType& {
            return *elem;
        }

    private:
        template<typename>
        friend class mixin::ConstArrayLike;

        template<typename>
        friend class mixin::ArrayLike;

    protected:
        ElemType elems[MAX_SIZE];
    };
}

#endif //OBJECT_ARRAY_2_ARRAYHOLDER_H
