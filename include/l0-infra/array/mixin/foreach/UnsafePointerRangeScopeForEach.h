//
// Created by Darwin Yuan on 2021/7/13.
//

#ifndef OBJECT_ARRAY_2_680A9595068E4997A1E2CBC3A0514949
#define OBJECT_ARRAY_2_680A9595068E4997A1E2CBC3A0514949

#include <l0-infra/array/concept/Op.h>

namespace mixin {
    template<typename T>
    struct UnsafePointerScopedRangeForEach : T {
        using typename T::ObjectType;
        using typename T::SizeType;
        using typename T::BitMap;

    protected:
        template<bool TO_NON_CONST, __oP_cOnCePt(OP)>
        auto GetIndicesOp(OP &&op) const -> auto {
            if constexpr(TO_NON_CONST) {
                if constexpr(__wItH_iNdEx_Op(OP)) {
                    return [&op](ObjectType *p, auto i) -> auto {
                        return op(*p, i);
                    };
                } else {
                    return [&op](ObjectType *p) -> auto {
                        return op(*p);
                    };
                }
            } else {
                if constexpr(__wItH_iNdEx_Op(OP)) {
                    return [&op](ObjectType const* p, auto i) -> auto {
                        return op(*p, i);
                    };
                } else {
                    return [&op](ObjectType const* p) -> auto {
                        return op(*p);
                    };
                }
            }
        }

        template<bool TO_NON_CONST, __oP_cOnCePt(OP)>
        auto Unsafe_RangeScopeForEach(SizeType from, SizeType until, BitMap scope, OP &&op) const -> auto {
            return T::GetPointers().Unsafe_RangeScopeForEach(from, until, scope, T::template GetPointerOp<TO_NON_CONST>(std::forward<OP>(op)));
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

#endif //OBJECT_ARRAY_2_680A9595068E4997A1E2CBC3A0514949
