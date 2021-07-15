//
// Created by Darwin Yuan on 2021/7/10.
//

#ifndef OBJECT_ARRAY_2_96C636C448354B638950FC9C2B2D64E7
#define OBJECT_ARRAY_2_96C636C448354B638950FC9C2B2D64E7

#include <l0-infra/array/concept/Pred.h>
#include <l0-infra/base/InvokeConstMethod.h>

namespace mixin {
    template<typename T>
    struct SimpleFindExt : T {
        using typename T::ObjectType;
        using typename T::SizeType;
        using typename T::Maybe;

        using T::FindIndex;
        using T::Find;

        template<__pRed_CoNcEpT(PRED)>
        auto Find(PRED &&pred) -> ObjectType* {
            return __INVOKE_CONST_METHOD(Find(std::forward<PRED>(pred)));
        }

        template<__pRed_CoNcEpT(PRED)>
        auto FindIndex(PRED &&pred) -> Maybe {
            return __INVOKE_CONST_METHOD(FindIndex(std::forward<PRED>(pred)));
        }

        auto Find(ObjectType const& obj) const -> ObjectType const* {
            return Find(T::GetEqPred(obj));
        }

        auto Find(ObjectType const& obj) -> ObjectType* {
            return __INVOKE_CONST_METHOD(Find(obj));
        }

        auto FindIndex(ObjectType const& obj) const -> Maybe {
            return T::FindIndex(T::GetEqPred(obj));
        }

        auto FindIndex(ObjectType const& obj) -> Maybe {
            return __INVOKE_CONST_METHOD(FindIndex(obj));
        }

        template<__pRed_CoNcEpT(PRED)>
        auto Exists(PRED &&pred) const -> bool {
            return Find(std::forward<PRED>(pred)) != nullptr;
        }

        auto Exists(ObjectType const &obj) const -> bool {
            return Exists(T::GetEqPred(obj));
        }
    };
}

#endif //OBJECT_ARRAY_2_96C636C448354B638950FC9C2B2D64E7
