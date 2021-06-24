//
// Created by Darwin Yuan on 2021/6/20.
//

#ifndef OBJECT_ARRAY_SIMPLEFINDEXT_H
#define OBJECT_ARRAY_SIMPLEFINDEXT_H

#include <object-array/concept/SimpleFind.h>
#include <object-array/concept/Pred.h>
#include <cub/base/InvokeConstMethod.h>

namespace mixin {
    template<_concept::SimpleFind T>
    class SimpleFindExt : public T {
        using Self = T;
    public:
        using ObjectType = typename T::ObjectType;
        using SizeType = typename T::SizeType;

        using Self::Find;
        using Self::FindIndex;

        template<_concept::Pred<ObjectType, SizeType> PRED>
        auto Find(PRED &&pred) const -> ObjectType const* {
            return Self::template Find(std::forward<PRED>(pred));
        }

        auto Find(ObjectType const& obj) const -> auto* {
            return Self::template Find([&](auto&& elem) { return elem == obj;});
        }

        auto Find(ObjectType const& obj) -> auto* {
            return __INVOKE_CONST_METHOD(Find(obj));
        }

        auto FindIndex(ObjectType const& obj) const -> auto {
            return Self::template FindIndex([&](auto&& elem) { return elem == obj;});
        }

        auto FindIndex(ObjectType const& obj) -> auto {
            return __INVOKE_CONST_METHOD(FindIndex(obj));
        }

        template<_concept::Pred<ObjectType, SizeType> PRED>
        auto Exists(PRED &&pred) const -> bool {
            return Find(std::forward<PRED>(pred)) != nullptr;
        }

        auto Exists(ObjectType const &obj) const -> bool {
            return Exists([&](auto&& elem) { return obj == elem; });
        }
    };
}

#endif //OBJECT_ARRAY_SIMPLEFINDEXT_H
