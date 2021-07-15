//
// Created by Darwin Yuan on 2021/7/12.
//

#ifndef OBJECT_ARRAY_2_FAF4B3FCA271456AA0CD3443F3C7210A
#define OBJECT_ARRAY_2_FAF4B3FCA271456AA0CD3443F3C7210A

#include <l0-infra/array/view/ScopeView.h>

namespace mixin {
    template<typename T>
    struct ScopeViewFactory_R : T {
        using typename T::BitMap;

    protected:
        using typename T::ThisType;

    public:
        using T::Scope;
        using T::Exclude;

        auto Scope(BitMap scope) && -> ValueScopeView<ThisType> {
            return {T::ToThisType(), T::MaskScope(scope)};
        }
        auto Scope(BitMap scope) const && -> ValueScopeView<ThisType const> {
            return {T::ToThisType(), T::MaskScope(scope)};
        }
        auto Exclude(BitMap excluded) && -> auto {
            return std::move(*this).Scope(~excluded);
        }
        auto Exclude(BitMap excluded) const && -> auto {
            return std::move(*this).Scope(~excluded);
        }
    };
}

#endif //OBJECT_ARRAY_2_FAF4B3FCA271456AA0CD3443F3C7210A
