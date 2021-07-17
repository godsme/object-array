//
// Created by Darwin Yuan on 2021/7/11.
//

#ifndef OBJECT_ARRAY_2_07E4A79BCE8D4CD7951A97B7136FE946
#define OBJECT_ARRAY_2_07E4A79BCE8D4CD7951A97B7136FE946

#include <l0-infra/array/concept/Pred.h>

namespace mixin {
    template<typename T>
    struct EraseExt : T {
        using typename T::OffsetType;
        using typename T::ObjectType;
        using typename T::SizeType;

        template<__sImPlE_pReD_cOnCePt(PRED)>
        auto Unsafe_CleanUpIf(SizeType from, SizeType until, PRED&& pred) -> void {
            if(from == until) return;
            for(int i = until - 1; i >= from; --i) {
                if(T::IsPresent(i) && pred(T::GetObject(i))) T::Erase(i);
            }
        }

    public:
        using T::Erase;

        auto Remove(ObjectType const * p) -> void {
            auto index = T::ObjectToIndex(p);
            if (index) T::Erase(*index);
        }

        template<__sImPlE_pReD_cOnCePt(PRED)>
        auto RemoveIf(PRED&& pred) -> void {
            auto found = T::FindIndex(std::forward<PRED>(pred));
            if(found) T::Erase(*found);
        }

        template<__sImPlE_pReD_cOnCePt(PRED)>
        auto CleanUpIf(PRED&& pred) -> void {
            Unsafe_CleanUpIf(T::IndexBegin(), T::IndexEnd(), std::forward<PRED>(pred));
        }

        template<__sImPlE_pReD_cOnCePt(PRED)>
        auto RangeCleanUpIf(OffsetType from, OffsetType until, PRED&& pred) -> void {
            Unsafe_CleanUpIf(from.ToIndex(T::IndexEnd()), until.ToIndex(T::IndexEnd()), std::forward<PRED>(pred));
        }

        template<__sImPlE_pReD_cOnCePt(PRED)>
        auto CleanUpFromIf(OffsetType from, PRED&& pred) -> void {
            Unsafe_CleanUpIf(from.ToIndex(T::IndexEnd()), T::IndexEnd(), std::forward<PRED>(pred));
        }

        template<__sImPlE_pReD_cOnCePt(PRED)>
        auto CleanUpUntilIf(OffsetType until, PRED&& pred) -> void {
            Unsafe_CleanUpIf(T::IndexBegin(), until.ToIndex(T::IndexEnd()), std::forward<PRED>(pred));
        }
    };
}

#endif //OBJECT_ARRAY_2_07E4A79BCE8D4CD7951A97B7136FE946
