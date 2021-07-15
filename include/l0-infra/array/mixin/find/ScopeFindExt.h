//
// Created by Darwin Yuan on 2021/7/10.
//

#ifndef OBJECT_ARRAY_2_56921B5DD9044F3E96EE492FEC17F69B
#define OBJECT_ARRAY_2_56921B5DD9044F3E96EE492FEC17F69B

#include <l0-infra/array/concept/Pred.h>
#include <l0-infra/base/InvokeConstMethod.h>

namespace mixin {
    template<typename T>
    struct ScopeFindExt : T {
        using typename T::ObjectType;
        using typename T::SizeType;
        using typename T::BitMap;
        using typename T::Maybe;

    public:
        using T::Find;
        using T::FindIndex;
        using T::Exists;

        template<__pRed_CoNcEpT(PRED)>
        auto FindIndex(BitMap scope, PRED &&pred) const -> Maybe {
            return T::Unsafe_ScopeFindIndex(scope.Mask(T::IndexBegin(), T::IndexEnd()), std::forward<PRED>(pred));
        }

        template<__pRed_CoNcEpT(PRED)>
        auto Find(BitMap scope, PRED &&pred) const -> ObjectType const* {
            auto index = FindIndex(scope, std::forward<PRED>(pred));
            return index ? &T::GetObject(*index) : nullptr;
        }

        template<__pRed_CoNcEpT(PRED)>
        auto FindEx(BitMap excluded, PRED &&pred) const -> ObjectType const* {
            return Find(~excluded, std::forward<PRED>(pred));
        }

        template<__pRed_CoNcEpT(PRED)>
        auto Find(BitMap scope, PRED &&pred) -> ObjectType* {
            return __INVOKE_CONST_METHOD(Find(scope, std::forward<PRED>(pred)));
        }

        template<__pRed_CoNcEpT(PRED)>
        auto FindEx(BitMap excluded, PRED &&pred) -> ObjectType* {
            return __INVOKE_CONST_METHOD(FindEx(excluded, std::forward<PRED>(pred)));
        }

        auto Find(BitMap scope, ObjectType const& obj) const -> ObjectType const* {
            return Find(scope, T::GetEqPred(obj));
        }

        auto FindEx(BitMap excluded, ObjectType const& obj) const -> ObjectType const* {
            return FindEx(excluded, T::GetEqPred(obj));
        }

        auto Find(BitMap scope, ObjectType const& obj) -> ObjectType* {
            return __INVOKE_CONST_METHOD(Find(scope, obj));
        }

        auto FindEx(BitMap excluded, ObjectType const& obj) -> ObjectType* {
            return __INVOKE_CONST_METHOD(FindEx(excluded, obj));
        }

        template<__pRed_CoNcEpT(PRED)>
        auto FindIndexEx(BitMap excluded, PRED &&pred) const -> Maybe {
            return FindIndex(~excluded, std::forward<PRED>(pred));
        }

        auto FindIndex(BitMap scope, ObjectType const& obj) const -> Maybe {
            return FindIndex(scope, T::GetEqPred(obj));
        }

        auto FindIndexEx(BitMap excluded, ObjectType const& obj) const -> Maybe {
            return FindIndexEx(excluded, T::GetEqPred(obj));
        }

        template<__pRed_CoNcEpT(PRED)>
        auto Exists(BitMap scope, PRED &&pred) const -> bool {
            return Find(scope, std::forward<PRED>(pred)) != nullptr;
        }

        template<__pRed_CoNcEpT(PRED)>
        auto ExistsEx(BitMap excluded, PRED &&pred) const -> bool {
            return FindEx(excluded, std::forward<PRED>(pred)) != nullptr;
        }

        auto Exists(BitMap scope, ObjectType const &obj) const -> bool {
            return Exists(scope, T::GetEqPred(obj));
        }

        auto ExistsEx(BitMap excluded, ObjectType const &obj) const -> bool {
            return ExistsEx(excluded, T::GetEqPred(obj));
        }
    };
}

#endif //OBJECT_ARRAY_2_56921B5DD9044F3E96EE492FEC17F69B
