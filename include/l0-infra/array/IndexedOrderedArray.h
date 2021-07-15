//
// Created by Darwin Yuan on 2021/7/12.
//

#ifndef OBJECT_ARRAY_2_D64C4CE0528646E29E6ACAE2E6D1B7A3
#define OBJECT_ARRAY_2_D64C4CE0528646E29E6ACAE2E6D1B7A3

#include <l0-infra/array/detail/IndexedArray.h>
#include <l0-infra/array/holder/IndexedOrderedArrayHolder.h>
#include <l0-infra/array/ScatteredArray.h>

namespace indexed_ordered_array {
    template<typename ARRAY, typename LESS>
    class Array : public indexed_array::Public::Compose<holder::IndexedOrderedArrayHolder<ARRAY, LESS>, indexed_array::Private, Array<ARRAY, LESS>> {
        using Parent = indexed_array::Public::Compose<holder::IndexedOrderedArrayHolder<ARRAY, LESS>, indexed_array::Private, Array<ARRAY, LESS>>;

    public:
        using typename Parent::ObjectType;

    public:
        using Parent::Parent;
        Array() {}
        Array(LESS const& less) : Parent{less} {}
        Array(LESS const& less, std::initializer_list<ObjectType> l) : Parent{less} {
            auto n = 0;
            for(auto i = l.begin(); i < l.end(); ++i) {
                if(n++ == Parent::MAX_SIZE) break;
                Parent::Append(*i);
            }
        }

        Array(std::initializer_list<ObjectType> l) : Array{LESS{}, l} {}

    private:
        template<typename>
        friend class mixin::ViewObjectLess;

        template<typename>
        friend class mixin::ViewObjectEquality;
    };
}

template<typename OBJ, std::size_t MAX_NUM, typename LESS = std::less<OBJ>>
using IndexedOrderedArray = indexed_ordered_array::Array<ScatteredArray<OBJ, MAX_NUM>, LESS>;

#endif //OBJECT_ARRAY_2_D64C4CE0528646E29E6ACAE2E6D1B7A3
