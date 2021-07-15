//
// Created by Darwin Yuan on 2021/7/13.
//

#ifndef OBJECT_ARRAY_2_A4DFE7D71053452BBE29ADC083340FAD
#define OBJECT_ARRAY_2_A4DFE7D71053452BBE29ADC083340FAD

#include <utility>

namespace mixin {
    template<typename T>
    struct ProxyAppend : T {
        using typename T::ObjectType;
        using typename T::Maybe;

    protected:
        using T::This;

    public:
        template<typename ... ARGS>
        auto Append_I(ARGS&& ... args) -> Maybe {
            return This()->DoAppend_I(std::forward<ARGS>(args)...);
        }

        template<typename ... ARGS>
        auto Append(ARGS&& ... args) -> ObjectType* {
            return This()->DoAppend(std::forward<ARGS>(args)...);
        }
    };
}

#endif //OBJECT_ARRAY_2_A4DFE7D71053452BBE29ADC083340FAD
