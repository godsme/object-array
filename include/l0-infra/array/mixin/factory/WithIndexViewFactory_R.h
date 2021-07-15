//
// Created by Darwin Yuan on 2021/7/11.
//

#ifndef OBJECT_ARRAY_2_99687B7E43A94F5DA77112C14EE70B1A
#define OBJECT_ARRAY_2_99687B7E43A94F5DA77112C14EE70B1A

#include <l0-infra/array/mixin/factory/WithIndexViewFactory.h>

namespace mixin::detail {
    template<typename T, typename VIEW>
    struct WithIndexViewFactory_R : detail::WithIndexViewFactory<T, VIEW> {
        using Self = WithIndexViewFactory<T, VIEW>;
        using typename T::ThisType;

        using Self::WithIndex;

        auto WithIndex() && -> typename VIEW::template ValueView<ThisType> {
            return {T::ToThisType()};
        }

        auto WithIndex() const && -> typename VIEW::template ValueView<ThisType const> {
            return {T::ToThisType()};
        }
    };
}

namespace mixin {
    template<typename T>
    using WithIndexViewFactory_R = detail::WithIndexViewFactory_R<T, WithIndexView>;

    template<typename T>
    using SortViewWithIndexViewFactory_R = detail::WithIndexViewFactory_R<T, SortViewWithIndexView>;
}

#endif //OBJECT_ARRAY_2_99687B7E43A94F5DA77112C14EE70B1A
