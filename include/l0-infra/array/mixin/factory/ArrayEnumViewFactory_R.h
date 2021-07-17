//
// Created by Darwin Yuan on 2021/7/17.
//

#ifndef OBJECT_ARRAY_49B277A9DC0E4FE98AE1A46B22DA60B0
#define OBJECT_ARRAY_49B277A9DC0E4FE98AE1A46B22DA60B0

namespace mixin {
    template<typename T>
    struct ArrayEnumViewFactory_R : T {
        using T::Enumerate;

        auto Enumerate() && -> auto {
            return std::move(*this).WithIndex();
        }
        auto Enumerate() const && -> auto {
            return std::move(*this).WithIndex();
        }
    };
}

#endif //OBJECT_ARRAY_49B277A9DC0E4FE98AE1A46B22DA60B0
