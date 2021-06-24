//
// Created by Darwin Yuan on 2021/6/21.
//

#ifndef OBJECT_ARRAY_OBJECTARRAYDATAHOLDER_H
#define OBJECT_ARRAY_OBJECTARRAYDATAHOLDER_H

#include <object-array/holder/detail/ContinuousArrayDataHolderInterface.h>
#include <object-array/holder/ArrayDataHolder.h>
#include <cub/base/DeduceSizeType.h>

namespace holder {
    template<typename OBJ, std::size_t MAX_NUM>
    struct ObjectArrayDataHolder : ArrayDataHolder<OBJ, MAX_NUM> {
        using Parent = ArrayDataHolder<OBJ, MAX_NUM>;
        using SizeType = typename Parent::SizeType;
        using Trait = typename Parent::Trait;
        using Interface = detail::ContinuousArrayDataHolderInterface<ObjectArrayDataHolder>;

    private:
        template<typename>
        friend class detail::ContinuousArrayDataHolderInterface;

    public:
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

    private:
        SizeType num{};
    };
}

#endif //OBJECT_ARRAY_OBJECTARRAYDATAHOLDER_H
