//
// Created by Darwin Yuan on 2021/6/21.
//

#ifndef OBJECT_ARRAY_OBJECTTRAIT_H
#define OBJECT_ARRAY_OBJECTTRAIT_H

#include <cub/base/Placement.h>

namespace holder::detail {
    template<typename ELEM>
    struct ObjectTrait {
        using ElemType = ELEM;
        using ObjectType = ELEM;

        static auto ToObject(ElemType const& elem) -> ObjectType const& { return elem; }
        static auto ToObject(ElemType& elem) -> ObjectType& { return elem; }

        template<typename ... ARGS>
        static auto Emplace(ElemType& elem, ARGS&& ... args) -> ObjectType* {
            if constexpr(!(sizeof...(args) == 0 && std::is_trivially_constructible_v<ObjectType>)) {
                if constexpr(std::is_aggregate_v<ElemType>) {
                    elem = ObjectType{std::forward<ARGS>(args)...};
                } else {
                    elem = ObjectType(std::forward<ARGS>(args)...);
                }
            }

            return &elem;
        }
    };

    template<typename OBJ>
    struct ObjectTrait<Placement<OBJ>> {
        using ElemType = Placement<OBJ>;
        using ObjectType = OBJ;

        static auto ToObject(ElemType const& elem) -> ObjectType const& { return elem.GetRef(); }
        static auto ToObject(ElemType& elem) -> ObjectType& { return elem.GetRef(); }

        template<typename ... ARGS>
        static auto Emplace(ElemType& elem, ARGS&& ... args) -> ObjectType* {
            return elem.template Emplace(std::forward<ARGS>(args)...);
        }
    };
}

#endif //OBJECT_ARRAY_OBJECTTRAIT_H
