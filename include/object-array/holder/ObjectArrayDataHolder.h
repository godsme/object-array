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
        using Trait = typename Parent::Trait;
        using Concept = detail::ArrayDataHolderConcept<ObjectArrayDataHolder>;

        ObjectArrayDataHolder() {}
        ObjectArrayDataHolder(std::initializer_list<OBJ> list) {
            auto n = std::min(list.size(), MAX_NUM);
            num = 0;
            for(auto&& elem : list) {
                Trait::Emplace(Parent::elems[num++], elem);
            }
        }

        ObjectArrayDataHolder(ObjectArrayDataHolder&& rhs) : num{rhs.num} {
            for(auto i=0; i<num; i++) {
                Trait::Emplace(Parent::elems[i], std::move(Parent::ElemToObject(rhs.elems[i])));
            }
        }

        auto Num() const -> SizeType { return num; }
        auto Num() -> decltype(auto) { return (num); }

    private:
        SizeType num{};
    };
}

#endif //OBJECT_ARRAY_OBJECTARRAYDATAHOLDER_H
