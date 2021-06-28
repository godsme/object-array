//
// Created by Darwin Yuan on 2021/6/25.
//

#ifndef OBJECT_ARRAY_CONCEPTDEF_H
#define OBJECT_ARRAY_CONCEPTDEF_H

#include <l0-infra/array/detail/config.h>

#if HAS_CONCEPT
#define __cOnCePt(c) typename
#define __pRed_CoNcEpT(PRED) _concept::Pred<ObjectType, SizeType> PRED
#define __wItH_iNdEx_pReD(PRED) _concept::WithIndexPred<PRED, ObjectType, SizeType>
#define __wItH_iNdEx_Op(OP) _concept::WithIndexOp<OP, ObjectType, SizeType>
#define __oP_cOnCePt(OP) _concept::Op<ObjectType, SizeType> OP
#define __lEsS_cOnCePt(LESS) _concept::Less<ObjectType> LESS
#define __sImPlE_pReD_cOnCePt(PRED) _concept::SimplePred<ObjectType> PRED
#else
#define __cOnCePt(c) typename

#define __sImPlE_pReD(PRED) std::is_invocable_r_v<bool, PRED, ObjectType const&>
#define __wItH_iNdEx_pReD(PRED) std::is_invocable_r_v<bool, PRED, ObjectType const&, SizeType>
#define __pRed_CoNcEpT(PRED) typename PRED, std::enable_if_t<__sImPlE_pReD(PRED) || __wItH_iNdEx_pReD(PRED), int> = 0
#define __sImPlE_pReD_cOnCePt(PRED) typename PRED, std::enable_if_t<__sImPlE_pReD(PRED), int> = 0

#define __sImPlE_Op(OP) std::is_invocable_v<OP, ObjectType&>
#define __wItH_iNdEx_Op(OP) std::is_invocable_v<OP, ObjectType&, SizeType>
#define __oP_cOnCePt(OP) typename OP, std::enable_if_t<(__sImPlE_Op(OP) || __wItH_iNdEx_Op(OP)), int> = 0

#define __lEsS_cOnCePt(LESS) typename LESS, std::enable_if_t<std::is_invocable_r_v<bool, LESS, ObjectType const&, ObjectType const&>, int> = 0
#endif

#endif //OBJECT_ARRAY_CONCEPTDEF_H
