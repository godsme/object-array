//
// Created by Darwin Yuan on 2021/6/24.
//

#ifndef OBJECT_ARRAY_SCOPEDFINDEXT_H
#define OBJECT_ARRAY_SCOPEDFINDEXT_H

#include <object-array/concept/RangedArrayLike.h>
#include <object-array/concept/Pred.h>
#include <object-array/mixin/ScopedFind.h>
#include <cub/base/InvokeConstMethod.h>

namespace mixin {
    template<_concept::ConstRangedArrayLike T>
    class ScopedFindExt : public ScopedFind<T> {
        using Self = ScopedFind<T>;
    public:
        using typename T::ObjectType;
        using typename T::SizeType;
        using typename T::BitMap;
        using typename T::Maybe;

        using Self::Find;
        using Self::FindIndex;
        using Self::Exists;

        template<_concept::Pred<ObjectType, SizeType> PRED>
        auto Find(BitMap scope, PRED &&pred) const -> ObjectType const* {
            return Self::template DoFind(scope, std::forward<PRED>(pred));
        }

        template<_concept::Pred<ObjectType, SizeType> PRED>
        auto FindEx(BitMap excluded, PRED &&pred) const -> ObjectType const* {
            return Find(~excluded, std::forward<PRED>(pred));
        }

        template<_concept::Pred<ObjectType, SizeType> PRED>
        auto Find(BitMap scope, PRED &&pred) -> ObjectType* {
            return __INVOKE_CONST_METHOD(Find(scope, std::forward<PRED>(pred)));
        }

        template<_concept::Pred<ObjectType, SizeType> PRED>
        auto FindEx(BitMap excluded, PRED &&pred) -> ObjectType* {
            return __INVOKE_CONST_METHOD(FindEx(excluded, std::forward<PRED>(pred)));
        }

        auto Find(BitMap scope, ObjectType const& obj) const -> ObjectType const* {
            return Find(scope, [&](auto&& elem) { return elem == obj;});
        }

        auto FindEx(BitMap excluded, ObjectType const& obj) const -> ObjectType const* {
            return FindEx(excluded, [&](auto&& elem) { return elem == obj;});
        }

        auto Find(BitMap scope, ObjectType const& obj) -> ObjectType* {
            return __INVOKE_CONST_METHOD(Find(scope, obj));
        }

        auto FindEx(BitMap excluded, ObjectType const& obj) -> ObjectType* {
            return __INVOKE_CONST_METHOD(FindEx(excluded, obj));
        }

        template<_concept::Pred<ObjectType, SizeType> PRED>
        auto FindIndex(BitMap scope, PRED &&pred) const -> Maybe {
            return Self::template DoFindIndex(scope, std::forward<PRED>(pred));
        }

        template<_concept::Pred<ObjectType, SizeType> PRED>
        auto FindIndexEx(BitMap excluded, PRED &&pred) const -> Maybe {
            return FindIndex(~excluded, std::forward<PRED>(pred));
        }

        auto FindIndex(BitMap scope, ObjectType const& obj) const -> Maybe {
            return FindIndex(scope, [&](auto&& elem) { return elem == obj;});
        }

        auto FindIndexEx(BitMap excluded, ObjectType const& obj) const -> Maybe {
            return FindIndexEx(excluded, [&](auto&& elem) { return elem == obj;});
        }

        template<_concept::Pred<ObjectType, SizeType> PRED>
        auto Exists(BitMap scope, PRED &&pred) const -> bool {
            return Find(scope, std::forward<PRED>(pred)) != nullptr;
        }

        template<_concept::Pred<ObjectType, SizeType> PRED>
        auto ExistsEx(BitMap excluded, PRED &&pred) const -> bool {
            return FindEx(excluded, std::forward<PRED>(pred)) != nullptr;
        }

        auto Exists(BitMap scope, ObjectType const &obj) const -> bool {
            return Exists(scope, [&](auto&& elem) { return obj == elem; });
        }

        auto ExistsEx(BitMap excluded, ObjectType const &obj) const -> bool {
            return ExistsEx(excluded, [&](auto&& elem) { return obj == elem; });
        }
    };
}

#endif //OBJECT_ARRAY_SCOPEDFINDEXT_H
