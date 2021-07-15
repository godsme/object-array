//
// Created by Darwin Yuan on 2021/7/11.
//

#ifndef OBJECT_ARRAY_2_46DC069C4A394651B62260CC019122FC
#define OBJECT_ARRAY_2_46DC069C4A394651B62260CC019122FC

#include <l0-infra/array/concept/Pred.h>

namespace mixin {
    template<typename T>
    struct AppendExt : T {
        using typename T::ObjectType;

    public:
        using T::Append;
        using T::Append_I;

        template<__sImPlE_pReD_cOnCePt(PRED), typename ... ARGS>
        auto FindOrAppend(PRED &&pred, ARGS&& ... args) -> ObjectType * {
            auto *found = T::Find(std::forward<PRED>(pred));
            return found != nullptr ? found : T::Append(std::forward<ARGS>(args)...);
        }

        auto FindOrAppend(ObjectType const& obj) -> ObjectType * {
            return FindOrAppend([&](auto&& elem) { return obj == elem; }, obj);
        }
    };
}

#endif //OBJECT_ARRAY_2_46DC069C4A394651B62260CC019122FC
