//
// Created by Darwin Yuan on 2021/7/14.
//

#ifndef OBJECT_ARRAY_2_309676F2EDAC487EB99C2EDDDD20CD0D
#define OBJECT_ARRAY_2_309676F2EDAC487EB99C2EDDDD20CD0D

#include <l0-infra/array/detail/IndexedArray.h>
#include <l0-infra/array/holder/IndexedArrayHolder.h>

namespace indexed_array {
    template<typename HOLDER>
    class Array : public Public::Compose<HOLDER, Private, Array<HOLDER>> {
        using Parent = Public::Compose<HOLDER, Private, Array<HOLDER>>;

    public:
        using typename Parent::ObjectType;

    public:
        using Parent::Parent;
        Array() {}

    private:
        template<typename>
        friend class mixin::ViewObjectLess;

        template<typename>
        friend class mixin::ViewObjectEquality;
    };
}

template<typename OBJ, std::size_t MAX_NUM>
using IndexedArray = indexed_array::Array<holder::IndexedArrayHolder<OBJ, MAX_NUM>>;

#endif //OBJECT_ARRAY_2_309676F2EDAC487EB99C2EDDDD20CD0D
