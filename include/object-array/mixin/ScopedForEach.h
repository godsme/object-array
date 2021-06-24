//
// Created by Darwin Yuan on 2021/6/24.
//

#ifndef OBJECT_ARRAY_SCOPEDFOREACH_H
#define OBJECT_ARRAY_SCOPEDFOREACH_H

#include <object-array/mixin/detail/ForEachCodeBlock.h>
#include <object-array/concept/RangedArrayLike.h>
#include <object-array/concept/Op.h>
#include <object-array/concept/ElemVisitor.h>

namespace mixin {
    template<_concept::OpVisitable T>
    class ScopedForEach : public T {
        using Self = T;
    public:
        using ObjectType = typename Self::ObjectType;
        using SizeType = typename Self::SizeType;
        using BitMap = typename Self::BitMap;

    public:
        using Self::IndexBegin;
        using Self::IndexEnd;

    public:
        template<bool TO_NON_CONST, bool SCOPE_CHECK, _concept::Op<ObjectType, SizeType> OP>
        auto DoForEach(BitMap scope, OP &&op) const -> auto {
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
