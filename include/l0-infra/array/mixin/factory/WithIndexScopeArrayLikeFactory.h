//
// Created by Darwin Yuan on 2021/7/12.
//

#ifndef OBJECT_ARRAY_2_8ED7AA0ADB234103A69903EDC0468E97
#define OBJECT_ARRAY_2_8ED7AA0ADB234103A69903EDC0468E97

#include <l0-infra/array/view/WithIndexScopeView.h>

namespace mixin {
    template<typename T>
    struct WithIndexScopeArrayLikeFactory : T {
    protected:
        using typename T::ThisType;

    public:
        auto WithIndex() && = delete;
        auto WithIndex() const&& = delete;

        auto WithIndex() & -> RefWithIndexScopeView<ThisType> { return {T::ToThisType()}; }
        auto WithIndex() const& -> RefWithIndexScopeView<ThisType const> { return {T::ToThisType()}; }
    };
}

#endif //OBJECT_ARRAY_2_8ED7AA0ADB234103A69903EDC0468E97
