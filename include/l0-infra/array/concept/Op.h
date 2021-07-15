//
// Created by Darwin Yuan on 2021/7/10.
//

#ifndef OBJECT_ARRAY_2_OP_D492B0D56E0B457A97C2BD057E8264E5
#define OBJECT_ARRAY_2_OP_D492B0D56E0B457A97C2BD057E8264E5

#include <type_traits>

#define __sImPlE_Op(OP) std::is_invocable_v<OP, ObjectType&>
#define __wItH_iNdEx_Op(OP) std::is_invocable_v<OP, ObjectType&, SizeType>
#define __oP_cOnCePt(OP) typename OP, std::enable_if_t<(__sImPlE_Op(OP) || __wItH_iNdEx_Op(OP)), int> = 0

#endif //OBJECT_ARRAY_2_OP_D492B0D56E0B457A97C2BD057E8264E5
