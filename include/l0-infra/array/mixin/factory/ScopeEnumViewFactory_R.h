//
// Created by Darwin Yuan on 2021/7/17.
//

#ifndef OBJECT_ARRAY_2F57396564B2464F8426F5000369657D
#define OBJECT_ARRAY_2F57396564B2464F8426F5000369657D

#include <l0-infra/array/view/WithIndexScopeView.h>

namespace mixin {
    template<typename T>
    struct ScopeEnumViewFactory_R : T {
        using typename T::ThisType;

        using T::Enumerate;

        auto Enumerate() && -> EnumerateScopeView::ValueView<ThisType> {
            return {T::ToThisType()};
        }

        auto Enumerate() const && -> EnumerateScopeView::ValueView<ThisType const> {
            return {T::ToThisType()};
        }
    };
}

#endif //OBJECT_ARRAY_2F57396564B2464F8426F5000369657D
