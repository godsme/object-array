//
// Created by Darwin Yuan on 2021/7/17.
//

#ifndef OBJECT_ARRAY_1DE1CF531B1A4D7A810A3FDCF3339CEA
#define OBJECT_ARRAY_1DE1CF531B1A4D7A810A3FDCF3339CEA

#include <l0-infra/array/concept/Op.h>
#include <l0-infra/array/concept/Pred.h>
#include <l0-infra/array/mixin/detail/ForEachCodeBlock.h>

namespace mixin {
    template<typename T>
    struct UnsafeRangePredForEach : T {
        using typename T::ObjectType;
        using typename T::SizeType;

    protected:
        template<bool TO_NON_CONST, typename PRED, __oP_cOnCePt(OP), __wItH_pReD(PRED)>
        auto Unsafe_RangePredForEach(SizeType from, SizeType until, PRED&& pred, OP &&op) const -> auto {
            for (auto i = from; i < until; i++) {
                if constexpr(__wItH_iNdEx_pReD(PRED)) {
                    if (!pred(T::GetObject(i), i)) continue;
                } else {
                    if (!pred(T::GetObject(i))) continue;
                }
                __vIsIt_CoDe_BlOcK__
            }
            __fOrEaCh_SuCcEsS_rEtUrN__
        }

    public:
        template<typename PRED, __oP_cOnCePt(OP), __wItH_pReD(PRED)>
        auto Unsafe_RangePredForEach(SizeType from, SizeType until, PRED&& pred, OP &&op) const -> auto {
            return Unsafe_RangePredForEach<false>(from, until, std::forward<PRED>(pred), std::forward<OP>(op));
        }

        template<typename PRED, __oP_cOnCePt(OP), __wItH_pReD(PRED)>
        auto Unsafe_RangePredForEach(SizeType from, SizeType until, PRED&& pred, OP &&op) -> auto {
            return Unsafe_RangePredForEach<true>(from, until, std::forward<PRED>(pred), std::forward<OP>(op));
        }
    };
}

#endif //OBJECT_ARRAY_1DE1CF531B1A4D7A810A3FDCF3339CEA
