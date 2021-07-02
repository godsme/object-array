//
// Created by Darwin Yuan on 2021/6/25.
//

#ifndef OBJECT_ARRAY_ERASEEXT_H
#define OBJECT_ARRAY_ERASEEXT_H

#include <l0-infra/array/concept/SimpleFind.h>
#include <l0-infra/array/concept/SimpleMutable.h>
#include <l0-infra/array/concept/Pred.h>

namespace mixin {
    template<__cOnCePt(SimpleFindMutable) T>
    class EraseExt : public T {
        using Self = T;

    protected:
        using Self::IndexBegin;
        using Self::IndexEnd;
        using Self::GetObj;

    public:
        using typename Self::ObjectType;

    protected:
        using Self::GetObjIndex;

    public:
        using Self::Erase;

        auto Remove(ObjectType const * p) -> void {
            auto index = GetObjIndex(p);
            if (index) Self::Erase(*index);
        }

        template<__sImPlE_pReD_cOnCePt(PRED)>
        auto RemoveBy(PRED&& pred) -> void {
            auto found = Self::FindIndex(std::forward<PRED>(pred));
            if(found) Self::Erase(*found);
        }

        template<__sImPlE_pReD_cOnCePt(PRED)>
        auto CleanUpBy(PRED&& pred) -> void {
            if(IndexBegin() == IndexEnd()) return;
            for(int i = IndexEnd() - 1; i >=IndexBegin(); --i) {
                if(pred(GetObj(i))) Self::Erase(i);
            }
        }
    };
}

#endif //OBJECT_ARRAY_ERASEEXT_H
