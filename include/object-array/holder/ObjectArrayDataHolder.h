//
// Created by Darwin Yuan on 2021/6/21.
//

#ifndef OBJECT_ARRAY_OBJECTARRAYDATAHOLDER_H
#define OBJECT_ARRAY_OBJECTARRAYDATAHOLDER_H

#include <cub/base/DeduceSizeType.h>
#include <object-array/holder/ArrayDataHolder.h>
#include <object-array/holder/detail/ArrayDataHolderConcept.h>

namespace holder {
    template<typename OBJ, std::size_t MAX_NUM>
    struct ObjectArrayDataHolder : ArrayDataHolder<OBJ, MAX_NUM> {
        using Parent = ArrayDataHolder<OBJ, MAX_NUM>;
        using SizeType = typename Parent::SizeType;
        using Concept = detail::ArrayDataHolderConcept<ObjectArrayDataHolder>;

        ObjectArrayDataHolder() {}
        ObjectArrayDataHolder(std::initializer_list<OBJ> list) {
            auto n = std::min(list.size(), MAX_NUM);
            num = 0;
            for(auto&& elem : list) {
                Parent::elems[num++] = elem;
            }
        }

        auto Num() const -> decltype(auto) { return (num); }
        auto Num() -> decltype(auto) { return (num); }

    private:
        SizeType num{};
    };
}

#endif //OBJECT_ARRAY_OBJECTARRAYDATAHOLDER_H
