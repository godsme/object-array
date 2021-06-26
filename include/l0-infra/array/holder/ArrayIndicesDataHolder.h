//
// Created by Darwin Yuan on 2021/6/26.
//

#ifndef OBJECT_ARRAY_ARRAYINDICESDATAHOLDER_H
#define OBJECT_ARRAY_ARRAYINDICESDATAHOLDER_H

#include <l0-infra/array/holder/ObjectArrayDataHolder.h>
#include <type_traits>

namespace holder {
    template<std::size_t MAX_SIZE, typename Parent = ObjectArrayDataHolder<DeduceSizeType_t<MAX_SIZE>, MAX_SIZE>>
    struct ArrayIndicesDataHolder : Parent {
        using Parent::Parent;

    private:
        using Parent::elems;
        using Parent::num;

    public:
        template<typename ARRAY, std::enable_if_t<(MAX_SIZE >= ARRAY::MAX_SIZE), bool> = true>
        auto InitWith(ARRAY const& array) -> void {
            for(num=0; num<array.GetNum(); num++) {
                elems[num] = num;
            }
        }

        template<typename ARRAY, std::enable_if_t<(MAX_SIZE >= ARRAY::MAX_SIZE), bool> = true>
        auto InitWithRange(ARRAY const& array) -> void {
            num = 0;
            for(auto i=array.IndexBegin(); i<array.IndexEnd(); i++) {
                elems[num++] = i;
            }
        }

        template<typename ARRAY, std::enable_if_t<(MAX_SIZE >= ARRAY::MAX_SIZE), bool> = true>
        auto InitWithRange(ARRAY const& array, typename ARRAY::BitMap scope) -> void {
            num = 0;
            for(auto i=array.IndexBegin(); i<array.IndexEnd() && scope.any(); i++) {
                if(scope.TestAndClear(i)) {
                    elems[num++] = i;
                }
            }
        }

        template<typename ARRAY, std::enable_if_t<(MAX_SIZE >= ARRAY::MAX_SIZE), bool> = true>
        auto InitWith(ARRAY const& array, typename ARRAY::BitMap scope) -> void {
            num = 0;
            auto total = array.GetNum();
            for(auto i=0; i<total && scope.any(); i++) {
                if(scope.TestAndClear(i)) {
                    elems[num++] = i;
                }
            }
        }
    };
}

#endif //OBJECT_ARRAY_ARRAYINDICESDATAHOLDER_H
