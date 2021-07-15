//
// Created by Darwin Yuan on 2021/7/10.
//

#ifndef OBJECT_ARRAY_2_9FAADE91699547F4B58CF7144AE05449
#define OBJECT_ARRAY_2_9FAADE91699547F4B58CF7144AE05449

#include <l0-infra/array/view/WithIndexView.h>

namespace mixin::detail {
    template<typename T, typename VIEW>
    struct WithIndexViewFactory : T {
        using typename T::ThisType;

        auto WithIndex() & -> typename VIEW::template RefView<ThisType> {
            return {T::ToThisType()};
        }

        auto WithIndex() const & -> typename VIEW::template RefView<ThisType const> {
            return {T::ToThisType()};
        }

        auto WithIndex() && = delete;
        auto WithIndex() const && = delete;
    };
}

namespace mixin {
    template<typename T>
    using WithIndexViewFactory = detail::WithIndexViewFactory<T, WithIndexView>;
}

#endif //OBJECT_ARRAY_2_9FAADE91699547F4B58CF7144AE05449
