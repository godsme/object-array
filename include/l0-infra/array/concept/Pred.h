//
// Created by Darwin Yuan on 2021/7/10.
//

#ifndef OBJECT_ARRAY_2_PRED_021878CC399F46C39EE95D4CEEC0427F
#define OBJECT_ARRAY_2_PRED_021878CC399F46C39EE95D4CEEC0427F

#include <type_traits>

#define __sImPlE_pReD(PRED) std::is_invocable_r_v<bool, PRED, ObjectType const&>
#define __wItH_iNdEx_pReD(PRED) std::is_invocable_r_v<bool, PRED, ObjectType const&, SizeType>
#define __pRed_CoNcEpT(PRED) typename PRED, std::enable_if_t<__sImPlE_pReD(PRED) || __wItH_iNdEx_pReD(PRED), int> = 0
#define __sImPlE_pReD_cOnCePt(PRED) typename PRED, std::enable_if_t<__sImPlE_pReD(PRED), int> = 0

#endif //OBJECT_ARRAY_2_PRED_021878CC399F46C39EE95D4CEEC0427F
