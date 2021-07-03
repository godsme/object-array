//
// Created by Darwin Yuan on 2021/7/3.
//

#ifndef OBJECT_ARRAY_CONTIGUOUSDOERASE_H
#define OBJECT_ARRAY_CONTIGUOUSDOERASE_H

#include <l0-infra/array/detail/ConceptDef.h>
#include <l0-infra/array/concept/ContiguousArrayLikeDataHolder.h>
#include <l0-infra/array/mixin/erase/SimpleDoErase.h>

namespace mixin {
    template<__cOnCePt(ContiguousArrayLikeDataHolder) T>
    class ContiguousDoErase : public SimpleDoErase<T> {
        using Self = SimpleDoErase<T>;

    public:
        using typename Self::SizeType;

    protected:
        using Self::Num;

    public:
        auto DoErase(SizeType i) -> void {
            --Num();
            Self::DoErase(i);
        }
    };
}

#endif //OBJECT_ARRAY_CONTIGUOUSDOERASE_H
