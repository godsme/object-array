//
// Created by Darwin Yuan on 2021/6/29.
//

#ifndef OBJECT_ARRAY____MUTABLE_MIXIN_DELIMITER____H
#define OBJECT_ARRAY____MUTABLE_MIXIN_DELIMITER____H

namespace mixin {
    template<typename T>
    struct ___mutable_mixin_delimiter___ final : T {
        constexpr static bool IS_CONST = T::IS_CONST;
    };
}

#endif //OBJECT_ARRAY____MUTABLE_MIXIN_DELIMITER____H
