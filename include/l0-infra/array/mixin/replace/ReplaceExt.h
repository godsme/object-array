//
// Created by Darwin Yuan on 2021/7/11.
//

#ifndef OBJECT_ARRAY_2_EDE40D7D04FE49D098F480105ABB38DE
#define OBJECT_ARRAY_2_EDE40D7D04FE49D098F480105ABB38DE

#include <l0-infra/array/concept/Pred.h>

namespace mixin {
    template<typename T>
    struct ReplaceExt : T {
        using typename T::ObjectType;
        using typename T::SizeType;

    public:
        using T::Replace;
        using T::Replace_I;

        template<__sImPlE_pReD_cOnCePt(PRED), typename ... ARGS>
        auto ReplaceBy(PRED&& pred, ARGS&& ... args) -> ObjectType * {
            auto index = T::FindIndex(std::forward<PRED>(pred));
            return index ? T::Replace(*index, std::forward<ARGS>(args)...) : nullptr;
        }

        template<typename ... ARGS>
        auto ReplaceObj(ObjectType const& obj, ARGS &&... args) -> ObjectType * {
            return ReplaceBy(T::GetEqPred(obj), std::forward<ARGS>(args)...);
        }

        template<typename ... ARGS>
        auto ReplaceObj(ObjectType const* p, ARGS &&... args) -> ObjectType * {
            auto index = T::ObjectToIndex(p);
            return index ? T::Replace(*index, std::forward<ARGS>(args)...) : nullptr;
        }
    };
}

#endif //OBJECT_ARRAY_2_EDE40D7D04FE49D098F480105ABB38DE
