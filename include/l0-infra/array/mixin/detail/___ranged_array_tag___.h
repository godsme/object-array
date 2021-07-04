//
// Created by Darwin Yuan on 2021/7/4.
//

#ifndef OBJECT_ARRAY____RANGED_ARRAY_TAG____H
#define OBJECT_ARRAY____RANGED_ARRAY_TAG____H

namespace mixin {
    template<typename T>
    struct ___ranged_array_tag___ : T {
        using RangedArrayLike = ___ranged_array_tag___;
    };
}

#endif //OBJECT_ARRAY____RANGED_ARRAY_TAG____H
