//
// Created by Darwin Yuan on 2021/7/15.
//

#ifndef OBJECT_ARRAY_665ECD459D564091983656BD0B82BA2F
#define OBJECT_ARRAY_665ECD459D564091983656BD0B82BA2F

#include <l0-infra/base/Placement.h>

namespace holder::detail {
    template<typename ELEM, typename OBJ>
    struct ObjectTrait {
        using ElemType = ELEM;
        using ObjectType = OBJ;

        static auto ConstToObject(ElemType const& elem) -> ObjectType const& { return elem; }
        static auto ToObject(ElemType& elem) -> ObjectType& { return elem; }

        template<typename ... ARGS>
        static auto Emplace(ElemType& elem, ARGS&& ... args) -> ObjectType* {
            if constexpr(sizeof...(args) != 0) {
                if constexpr(std::is_aggregate_v<ElemType>) {
                    elem = ObjectType{std::forward<ARGS>(args)...};
                } else {
                    elem = ObjectType(std::forward<ARGS>(args)...);
                }
            }
            return &elem;
        }

        static auto Destroy(ElemType & elem) -> void {}

        template<typename ... ARGS>
        static auto Replace(ElemType & elem, ARGS&& ... args) -> auto* {
            return Emplace(elem, std::forward<ARGS>(args) ...);
        }
    };

    template<typename OBJ>
    struct ObjectTrait<Placement<OBJ>, OBJ> {
        using ElemType = Placement<OBJ>;
        using ObjectType = OBJ;

        static auto ConstToObject(ElemType const& elem) -> ObjectType const& { return elem.GetRef(); }
        static auto ToObject(ElemType& elem) -> ObjectType& { return elem.GetRef(); }

        template<typename ... ARGS>
        static auto Emplace(ElemType& elem, ARGS&& ... args) -> ObjectType* {
            return elem.Emplace(std::forward<ARGS>(args)...);
        }

        static auto Destroy(ElemType & elem) -> void {
            elem.Destroy();
        }

        template<typename ... ARGS>
        static auto Replace(ElemType & elem, ARGS&& ... args) -> auto* {
            return elem.Replace(std::forward<ARGS>(args)...);
        }
    };
}

#endif //OBJECT_ARRAY_665ECD459D564091983656BD0B82BA2F
