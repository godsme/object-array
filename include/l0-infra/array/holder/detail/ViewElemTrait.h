//
// Created by Darwin Yuan on 2021/7/13.
//

#ifndef OBJECT_ARRAY_2_B75C48D2C4E14687A0F423B992F8FD1B
#define OBJECT_ARRAY_2_B75C48D2C4E14687A0F423B992F8FD1B

#include <type_traits>

namespace holder::detail {
    template<typename OBJ>
    struct ObjElemSameTrait {
        using ElemType = OBJ;
        using ObjectType = OBJ;

        static auto ConstObjToElem(ObjectType const& obj) -> decltype(auto) {
            return (obj);
        }

        static auto ObjToElem(ObjectType& obj) -> decltype(auto) {
            return (obj);
        }

        ObjElemSameTrait() = delete;
        ~ObjElemSameTrait() = delete;
    };

    template<typename OBJ, typename WRAPPER>
    struct ObjWrapperTrait {
        using ElemType = WRAPPER;
        using ObjectType = OBJ;

        static auto ConstObjToElem(ObjectType const& obj) -> decltype(auto) {
            return (WRAPPER::from(obj));
        }

        static auto ObjToElem(ObjectType& obj) -> decltype(auto) {
            return (WRAPPER::from(obj));
        }

        ObjWrapperTrait() = delete;
        ~ObjWrapperTrait() = delete;
    };

    template<typename OBJ, typename ELEM, bool = std::is_same_v<OBJ, ELEM>>
    struct ViewElemTrait {
        using Type = ObjElemSameTrait<OBJ>;
    };

    template<typename OBJ, typename ELEM>
    struct ViewElemTrait<OBJ, ELEM, false> {
        static_assert(sizeof(OBJ) == sizeof(ELEM));
        using ElemType = decltype(ELEM::from(std::declval<OBJ const&>()));
        using ObjectType  = decltype(std::declval<ELEM const&>().to_struct());
        static_assert(std::is_reference_v<ElemType>);
        static_assert(std::is_reference_v<ObjectType>);
        static_assert(std::is_same_v<std::decay_t<ElemType>, ELEM>);
        static_assert(std::is_same_v<std::decay_t<ObjectType>, OBJ>);

        using Type = ObjWrapperTrait<OBJ, ELEM>;
    };

    template<typename OBJ, typename ELEM>
    using ViewElemTrait_T = typename ViewElemTrait<OBJ, ELEM>::Type;
}

#endif //OBJECT_ARRAY_2_B75C48D2C4E14687A0F423B992F8FD1B
