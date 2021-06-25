//
// Created by Darwin Yuan on 2021/6/20.
//

#ifndef OBJECT_ARRAY_SIMPLEFINDEXT_H
#define OBJECT_ARRAY_SIMPLEFINDEXT_H

#include <object-array/concept/SimpleFind.h>
#include <object-array/concept/Pred.h>
#include <l0-infra/base/InvokeConstMethod.h>

namespace mixin {
    template<__cOnCePt(SimpleFind) T>
    class SimpleFindExt : public T {
        using Self = T;
    public:
        using typename T::ObjectType;
        using typename T::SizeType;
        using typename T::Maybe;

        using Self::Find;
        using Self::FindIndex;

        template<__pRed_CoNcEpT(PRED)>
        auto Find(PRED &&pred) -> ObjectType* {
            return __INVOKE_CONST_METHOD(Find(std::forward<PRED>(pred)));
        }

        template<__pRed_CoNcEpT(PRED)>
        auto FindIndex(PRED &&pred) -> Maybe {
            return __INVOKE_CONST_METHOD(FindIndex(std::forward<PRED>(pred)));
        }

        auto Find(ObjectType const& obj) const -> ObjectType const* {
            return Self::template Find([&](auto&& elem) { return elem == obj;});
        }

        auto Find(ObjectType const& obj) -> ObjectType* {
            return __INVOKE_CONST_METHOD(Find(obj));
        }

        auto FindIndex(ObjectType const& obj) const -> Maybe {
            return Self::template FindIndex([&](auto&& elem) { return elem == obj;});
        }

        auto FindIndex(ObjectType const& obj) -> Maybe {
            return __INVOKE_CONST_METHOD(FindIndex(obj));
        }

        template<__pRed_CoNcEpT(PRED)>
        auto Exists(PRED &&pred) const -> bool {
            return Find(std::forward<PRED>(pred)) != nullptr;
        }

        auto Exists(ObjectType const &obj) const -> bool {
            return Exists([&](auto&& elem) { return obj == elem; });
        }
    };
}

#endif //OBJECT_ARRAY_SIMPLEFINDEXT_H
