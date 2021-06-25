//
// Created by Darwin Yuan on 2021/6/25.
//

#ifndef OBJECT_ARRAY_PREDBASEDMUTATE_H
#define OBJECT_ARRAY_PREDBASEDMUTATE_H

#include <l0-infra/array/concept/SimpleFind.h>
#include <l0-infra/array/concept/SimpleMutable.h>
#include <l0-infra/array/concept/Pred.h>

namespace mixin {
#if HAS_CONCEPT
    template<typename T>
    concept SimpleFind_Mutable =
            _concept::SimpleRangedArrayLike<T> &&
            _concept::SimpleMutable<T> &&
            _concept::SimpleFind<T>;
    template<SimpleFind_Mutable T>
#else
    template<typename T>
#endif
    class PredBasedMutate : public T {
        using Self = T;

    public:
        using typename Self::ObjectType;

    public:
        using Self::Find;
        using Self::FindIndex;

        using Self::Append;
        using Self::Erase;

        using Self::IndexBegin;
        using Self::IndexEnd;
        using Self::GetObj;

    public:
        template<__sImPlE_pReD_cOnCePt(PRED)>
        auto FindOrAppend(PRED&& pred) -> ObjectType * {
            auto* found = Find(std::forward<PRED>(pred));
            return found != nullptr ? found : Append();
        }

        template<__sImPlE_pReD_cOnCePt(PRED)>
        auto RemoveBy(PRED&& pred) -> void {
            auto found = FindIndex(std::forward<PRED>(pred));
            if(found) Erase(*found);
        }

        template<__sImPlE_pReD_cOnCePt(PRED)>
        auto CleanUpBy(PRED&& pred) -> void {
            if(IndexBegin() == IndexEnd()) return;
            for(int i = IndexEnd() - 1; i >=IndexBegin(); --i) {
                if(pred(GetObj(i))) Erase(i);
            }
        }
    };
}
#endif //OBJECT_ARRAY_PREDBASEDMUTATE_H
