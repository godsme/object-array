//
// Created by Darwin Yuan on 2021/6/20.
//

#ifndef OBJECT_ARRAY_SIMPLEFINDEXT_H
#define OBJECT_ARRAY_SIMPLEFINDEXT_H

#include <object-array/detail/MixinDef.h>
#include <object-array/concept/SimpleFind.h>
#include <object-array/concept/Pred.h>
#include <cub/base/InvokeConstMethod.h>

namespace mixin {
    template<_concept::SimpleFind T>
    struct SimpleFindExt : private T {
        using ObjectType = typename T::ObjectType;
        using SizeType = typename T::SizeType;

        using T::Find;
        using T::FindIndex;

        template<_concept::Pred<ObjectType, SizeType> PRED>
        auto Find(PRED &&pred) const -> auto* {
            return Find(std::forward<PRED>(pred));
        }

        auto Find(ObjectType const& obj) -> auto* {
            return __INVOKE_CONST_METHOD(Find(obj));
        }

        auto FindIndex(ObjectType const& obj) const -> auto {
            return FindIndex([&](auto&& elem) { return elem == obj;});
        }

        auto FindIndex(ObjectType const& obj) -> auto {
            return __INVOKE_CONST_METHOD(FindIndex(obj));
        }
    };
}

#endif //OBJECT_ARRAY_SIMPLEFINDEXT_H
