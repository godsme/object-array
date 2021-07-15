//
// Created by Darwin Yuan on 2021/7/14.
//

#ifndef OBJECT_ARRAY_2_A54C38A6B8454B94B142285EF621F522
#define OBJECT_ARRAY_2_A54C38A6B8454B94B142285EF621F522

#include <l0-infra/array/iterator/detail/IndexIterator.h>

namespace iterator::detail {
    template<typename ARRAY, typename OBJ_TYPE, typename BASE_ITERATOR>
    struct ViewIterator : BASE_ITERATOR {
        using SizeType = typename ARRAY::SizeType;

        template<typename ... ARGS>
        ViewIterator(ARRAY& array, ARGS&& ... args)
            : BASE_ITERATOR(std::forward<ARGS>(args)...)
            , array{array} {}

        auto operator*() -> OBJ_TYPE& {
            return GetValue();
        }

    protected:
        using BASE_ITERATOR::StepForward;

        auto GetValue() -> OBJ_TYPE& {
            return array.GetObject(BASE_ITERATOR::GetValue());
        }

        auto GetValue() const -> OBJ_TYPE const& {
            return array.GetObject(BASE_ITERATOR::GetValue());
        }

    private:
        ARRAY& array;
    };
}

namespace iterator {
    template<typename ARRAY, typename OBJ_TYPE, typename SIZE_TYPE>
    using ViewIterator = detail::ViewIterator<ARRAY, OBJ_TYPE, detail::IndexIterator<SIZE_TYPE>>;
}

#endif //OBJECT_ARRAY_2_A54C38A6B8454B94B142285EF621F522
