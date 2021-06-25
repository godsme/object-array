//
// Created by Darwin Yuan on 2021/6/24.
//

#ifndef OBJECT_ARRAY_SIMPLEFOREACH_H
#define OBJECT_ARRAY_SIMPLEFOREACH_H

#include <l0-infra/array/mixin/detail/ForEachCodeBlock.h>
#include <l0-infra/array/concept/RangedArrayLike.h>
#include <l0-infra/array/concept/Op.h>
#include <l0-infra/array/concept/ElemVisitor.h>

namespace mixin {
    template<__cOnCePt(OpVisitable) T>
    class SimpleForEach : public T {
        using Self = T;

    public:
        using typename Self::SizeType;
        using typename Self::ObjectType;

    public:
        using Self::Visit;
        using Self::IndexBegin;
        using Self::IndexEnd;

    public:
        template<bool TO_NON_CONST, __oP_cOnCePt(OP)>
        auto DoForEach(OP &&op) const -> auto {
            for (auto i = IndexBegin(); i < IndexEnd(); i++) {
                __vIsIt_CoDe_BlOcK__
            }
            __fOrEaCh_SuCcEsS_rEtUrN__
        }
    };
}

#endif //OBJECT_ARRAY_SIMPLEFOREACH_H
