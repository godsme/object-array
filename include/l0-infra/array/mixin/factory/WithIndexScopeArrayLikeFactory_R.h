//
// Created by Darwin Yuan on 2021/7/12.
//

#ifndef OBJECT_ARRAY_2_F4781F28E0F34C4F85D2DC96F882840D
#define OBJECT_ARRAY_2_F4781F28E0F34C4F85D2DC96F882840D

#include <l0-infra/array/view/WithIndexScopeView.h>

namespace mixin {
    template<typename T>
    struct WithIndexScopeArrayLikeFactory_R : T {
    protected:
        using typename T::ThisType;

    public:
        using T::WithIndex;

        auto WithIndex() && -> WithIndexScopeView::ValueView<ThisType> {
            return {T::ToThisType()};
        }
        auto WithIndex() const&& -> WithIndexScopeView::ValueView<ThisType const> {
            return {T::ToThisType()};
        }
    };
}

#endif //OBJECT_ARRAY_2_F4781F28E0F34C4F85D2DC96F882840D
