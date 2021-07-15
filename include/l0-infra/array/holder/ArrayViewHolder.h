//
// Created by Darwin Yuan on 2021/7/13.
//

#ifndef OBJECT_ARRAY_2_8BBAFFE0818A4908B3AC6B5064CDA039
#define OBJECT_ARRAY_2_8BBAFFE0818A4908B3AC6B5064CDA039

#include <l0-infra/array/holder/detail/ViewElemTrait.h>
#include <l0-infra/array/mixin/array_like/ContiguousArrayLike.h>
#include <l0-infra/array/mixin/array_like/ConstArrayLike.h>
#include <algorithm>
#include <cstring>

namespace holder {
    template <typename OBJ, typename SIZE_TYPE, SIZE_TYPE MAX_NUM, typename ELEM, bool ORDERED>
    struct ArrayViewHolder {
        static_assert(std::is_trivial_v<OBJ>);
        using ElemType = ELEM;
        using ObjectType = ELEM;
        using SizeType = std::remove_const_t<SIZE_TYPE>;
        constexpr static SizeType MAX_SIZE = MAX_NUM;
        constexpr static bool IS_ORDERED = ORDERED;
        constexpr static auto IS_CONST = false;
        using ViewTrait = detail::ViewElemTrait_T<OBJ, ELEM>;

    public:
        ArrayViewHolder(OBJ* array, SIZE_TYPE& n)
                : elems((ElemType (&)[MAX_SIZE])ViewTrait::ObjToElem(*array))
                , num(n)
        {
            if(num > MAX_SIZE) num = MAX_SIZE;
        }

        ArrayViewHolder(ArrayViewHolder const& rhs)
                : elems{rhs.elems}, num(rhs.num) {}

        auto CopyFrom(OBJ const* array, std::size_t n) -> void {
            num = std::min(n, MAX_SIZE);
            ::memcpy(elems, array, sizeof(ELEM) * num);
        }

        auto operator=(ArrayViewHolder const& rhs) -> ArrayViewHolder& {
            CopyFrom(rhs.elems, rhs.num);
            return *this;
        }

        auto Clear() {
            num = 0;
        }

        auto ClearFrom(SizeType n) {
            num = std::min(num, n);
        }

    private:
        template <typename>
        friend class mixin::ContiguousArrayLike;

        template <typename>
        friend class mixin::ConstArrayLike;

        static auto ConstElemToObject(ElemType const& elem) -> ObjectType const& { return elem; }
        static auto ElemToObject(ElemType& elem) -> ObjectType& { return elem; }

    private:
        ElemType (&elems)[MAX_SIZE];
        SIZE_TYPE& num;
    };
}

#endif //OBJECT_ARRAY_2_8BBAFFE0818A4908B3AC6B5064CDA039
