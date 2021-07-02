//
// Created by Darwin Yuan on 2021/6/24.
//

#ifndef OBJECT_ARRAY_SCOPEDFOREACH_H
#define OBJECT_ARRAY_SCOPEDFOREACH_H

#include <l0-infra/array/mixin/detail/ForEachCodeBlock.h>
#include <l0-infra/array/concept/RangedArrayLike.h>
#include <l0-infra/array/concept/Op.h>
#include <l0-infra/array/concept/ElemVisitor.h>

namespace mixin {
    template<__cOnCePt(OpVisitable) T>
    class ScopedForEach : public T {
        using Self = T;
    public:
        using typename Self::ObjectType;
        using typename Self::SizeType;
        using typename Self::BitMap;

    public:
        using Self::IndexBegin;
        using Self::IndexEnd;

    public:
        template<bool TO_NON_CONST, bool SCOPE_CHECK, __oP_cOnCePt(OP)>
        auto DoScopeForEach(BitMap scope, OP &&op) const -> auto {
            scope.template Align<SCOPE_CHECK>(IndexBegin(), IndexEnd());
            for (auto i = IndexBegin(); scope.any(); scope >>= 1, ++i) {
                if (!scope[0]) continue;
                __vIsIt_CoDe_BlOcK__
            }
            __fOrEaCh_SuCcEsS_rEtUrN__
        }
    };
}

#endif //OBJECT_ARRAY_SCOPEDFOREACH_H
