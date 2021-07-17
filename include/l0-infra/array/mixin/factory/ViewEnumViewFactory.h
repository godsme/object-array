//
// Created by Darwin Yuan on 2021/7/17.
//

#ifndef OBJECT_ARRAY_1E40915612AB4FD39F66DBC6D0E1C673
#define OBJECT_ARRAY_1E40915612AB4FD39F66DBC6D0E1C673

#include <l0-infra/array/view/WithIndexView.h>

namespace mixin {
    template<typename T>
    struct EnumViewFactory : T {
        using typename T::ThisType;

        auto Enumerate() & -> EnumerateView::RefView<ThisType> {
            return {T::ToThisType()};
        }

        auto Enumerate() const & -> EnumerateView::RefView<ThisType const> {
            return {T::ToThisType()};
        }

        auto Enumerate() && -> EnumerateView::ValueView<ThisType> {
            return {T::ToThisType()};
        }

        auto Enumerate() const && -> EnumerateView::ValueView<ThisType const> {
            return {T::ToThisType()};
        }
    };
}

#endif //OBJECT_ARRAY_1E40915612AB4FD39F66DBC6D0E1C673
