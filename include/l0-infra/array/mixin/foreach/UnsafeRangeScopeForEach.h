//
// Created by Darwin Yuan on 2021/7/10.
//

#ifndef OBJECT_ARRAY_2_A745F7FE6FA8440B8544B695E94EAA70
#define OBJECT_ARRAY_2_A745F7FE6FA8440B8544B695E94EAA70

#include <l0-infra/array/concept/Op.h>
#include <l0-infra/array/mixin/detail/ForEachCodeBlock.h>

namespace mixin {
    template<typename T>
    struct UnsafeRangeScopeForEach : T {
        using typename T::ObjectType;
        using typename T::SizeType;
        using typename T::BitMap;

    protected:
        template<bool TO_NON_CONST, __oP_cOnCePt(OP)>
        auto Unsafe_RangeScopeForEach(SizeType from, SizeType until, BitMap scope, OP &&op) const -> auto {
            scope >>= from;
            for (auto i = from; scope.any(); scope >>= 1, ++i) {
                if (!scope[0]) continue;
                __vIsIt_CoDe_BlOcK__
            }
            __fOrEaCh_SuCcEsS_rEtUrN__
        }

    public:
        template<__oP_cOnCePt(OP)>
        auto Unsafe_RangeScopeForEach(SizeType from, SizeType until, BitMap scope, OP &&op) const -> auto {
            return Unsafe_RangeScopeForEach<false>(from, until, scope, std::forward<OP>(op));
        }

        template<__oP_cOnCePt(OP)>
        auto Unsafe_RangeScopeForEach(SizeType from, SizeType until, BitMap scope, OP &&op) -> auto {
            return Unsafe_RangeScopeForEach<true>(from, until, scope, std::forward<OP>(op));
        }
    };
}

#endif //OBJECT_ARRAY_2_A745F7FE6FA8440B8544B695E94EAA70
