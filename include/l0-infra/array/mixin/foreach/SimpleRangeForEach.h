//
// Created by Darwin Yuan on 2021/7/10.
//

#ifndef OBJECT_ARRAY_2_B4763B2454C24163A2C90E621DFFDA21
#define OBJECT_ARRAY_2_B4763B2454C24163A2C90E621DFFDA21

#include <l0-infra/array/concept/Op.h>
#include <l0-infra/array/mixin/detail/ForEachCodeBlock.h>

namespace mixin {
    template<typename T>
    class SimpleRangeForEach : public T {
        using Self = T;

    public:
        using typename Self::SizeType;
        using typename Self::ObjectType;

    public:
        using Self::Visit;

    public:
        template<bool TO_NON_CONST, __oP_cOnCePt(OP)>
        auto RangeForEach(SizeType from, SizeType until, OP &&op) const -> auto {
            for (auto i = from; i < until; i++) {
                __vIsIt_CoDe_BlOcK__
            }
            __fOrEaCh_SuCcEsS_rEtUrN__
        }
    };
}

#endif //OBJECT_ARRAY_2_B4763B2454C24163A2C90E621DFFDA21
