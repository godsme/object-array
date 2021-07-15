//
// Created by Darwin Yuan on 2021/7/15.
//

#ifndef OBJECT_ARRAY_C120B3BF0BD44CB5A155D050D85267CF
#define OBJECT_ARRAY_C120B3BF0BD44CB5A155D050D85267CF

#include <utility>

namespace mixin {
    template<typename T>
    struct ProxyReplace : T {
        using typename T::ObjectType;
        using typename T::SizeType;
        using typename T::Maybe;

    protected:
        using T::This;

    public:
        template<typename ... ARGS>
        auto Replace_I(SizeType n, ARGS&& ... args) -> Maybe {
            return This()->DoReplace_I(n, std::forward<ARGS>(args)...);
        }

        template<typename ... ARGS>
        auto Replace(SizeType n, ARGS&& ... args) -> ObjectType* {
            return This()->DoReplace(n, std::forward<ARGS>(args)...);
        }
    };
}

#endif //OBJECT_ARRAY_C120B3BF0BD44CB5A155D050D85267CF
