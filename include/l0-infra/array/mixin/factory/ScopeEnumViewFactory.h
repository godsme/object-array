//
// Created by Darwin Yuan on 2021/7/17.
//

#ifndef OBJECT_ARRAY_7093CBB104F44C59AAF333FF63E03C15
#define OBJECT_ARRAY_7093CBB104F44C59AAF333FF63E03C15

#include <l0-infra/array/view/WithIndexScopeView.h>

namespace mixin {
    template<typename T>
    struct ScopeEnumViewFactory : T {
        using typename T::ThisType;

        auto Enumerate() & -> EnumerateScopeView::RefView<ThisType> {
            return {T::ToThisType()};
        }

        auto Enumerate() const & -> EnumerateScopeView::RefView<ThisType const> {
            return {T::ToThisType()};
        }

        auto Enumerate() && = delete;
        auto Enumerate() const && = delete;
    };
}

#endif //OBJECT_ARRAY_7093CBB104F44C59AAF333FF63E03C15
