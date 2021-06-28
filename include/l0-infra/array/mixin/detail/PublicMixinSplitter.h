//
// Created by Darwin Yuan on 2021/6/28.
//

#ifndef OBJECT_ARRAY_PUBLICMIXINSPLITTER_H
#define OBJECT_ARRAY_PUBLICMIXINSPLITTER_H

namespace mixin::detail {
    template<typename T>
    struct PublicMixinSplitter : protected T {};
}

#endif //OBJECT_ARRAY_PUBLICMIXINSPLITTER_H
