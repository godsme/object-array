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
    };
}

#endif //OBJECT_ARRAY_2_07E4A79BCE8D4CD7951A97B7136FE946
