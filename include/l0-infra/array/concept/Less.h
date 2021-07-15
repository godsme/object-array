//
// Created by Darwin Yuan on 2021/7/9.
//

#ifndef OBJECT_ARRAY_2_LESS_H
#define OBJECT_ARRAY_2_LESS_H

#include <type_traits>

#define __lEsS_cOnCePt(LESS) typename LESS, std::enable_if_t<std::is_invocable_r_v<bool, LESS, ObjectType const&, ObjectType const&>, int> = 0

#endif //OBJECT_ARRAY_2_LESS_H
