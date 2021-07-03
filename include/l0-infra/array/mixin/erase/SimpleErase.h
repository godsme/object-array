//
// Created by Darwin Yuan on 2021/7/3.
//

#ifndef OBJECT_ARRAY_SIMPLEERASE_H
#define OBJECT_ARRAY_SIMPLEERASE_H

#include <l0-infra/array/detail/ConceptDef.h>
#include <l0-infra/array/concept/ContinuousArrayLikeDataHolder.h>
#include <l0-infra/array/mixin/erase/SimpleDoErase.h>

namespace mixin {
    template<__cOnCePt(ContinuousArrayLikeDataHolder) T>
    class SimpleErase : public SimpleDoErase<T> {
        using Self = SimpleDoErase<T>;

    public:
        using typename Self::SizeType;

    protected:
        using Self::Num;

    public:
        auto Erase(SizeType i) -> void {
            if (i < Num()) Self::DoErase(i);
        }
    };
}

#endif //OBJECT_ARRAY_SIMPLEERASE_H
