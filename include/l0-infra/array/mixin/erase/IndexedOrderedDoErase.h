//
// Created by Darwin Yuan on 2021/7/3.
//

#ifndef OBJECT_ARRAY_INDEXEDORDEREDDOERASE_H
#define OBJECT_ARRAY_INDEXEDORDEREDDOERASE_H

#include <l0-infra/array/detail/ConceptDef.h>
#include <l0-infra/array/concept/ContiguousArrayLikeDataHolder.h>
#include <l0-infra/array/mixin/erase/SimpleDoErase.h>

namespace mixin {
    template<__cOnCePt(ConstContiguousArrayLikeDataHolder) T>
    class IndexedOrderedDoErase : public T {
        using Self = T;

    public:
        using typename T::SizeType;

    protected:
        using Self::GetIndices;

    public:
        auto DoErase(SizeType n) -> void {
            auto index = GetIndices()[n];
            GetIndices().Erase(n);
            Self::Erase(index);
        }
    };
}

#endif //OBJECT_ARRAY_INDEXEDORDEREDDOERASE_H
