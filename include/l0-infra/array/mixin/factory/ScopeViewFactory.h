//
// Created by Darwin Yuan on 2021/7/12.
//

#ifndef OBJECT_ARRAY_2_DB1ED0F23E314BAAADC4033B3F2DDBA3
#define OBJECT_ARRAY_2_DB1ED0F23E314BAAADC4033B3F2DDBA3

#include <l0-infra/array/view/ScopeView.h>

namespace mixin {
    template<typename T>
    struct ScopeViewFactory : T {
        using typename T::SizeType;
        using typename T::ObjectType;
        using typename T::BitMap;

    protected:
        using typename T::ThisType;

        auto MaskScope(BitMap scope) const -> BitMap {
            return scope.Mask(T::IndexBegin(), T::IndexEnd());
        }

    public:
        auto Scope(BitMap scope) && = delete;
        auto Scope(BitMap scope) const && = delete;

        auto Scope(BitMap scope) & -> RefScopeView<ThisType> {
            return {T::ToThisType(), MaskScope(scope)};
        }

        auto Scope(BitMap scope) const & -> RefScopeView<ThisType const> {
            return {T::ToThisType(), MaskScope(scope)};
        }

        auto Exclude(BitMap excluded) && = delete;
        auto Exclude(BitMap excluded) const && = delete;

        auto Exclude(BitMap excluded) & -> auto {
            return Scope(~excluded);
        }

        auto Exclude(BitMap excluded) const & -> auto {
            return Scope(~excluded);
        }
    };
}

#endif //OBJECT_ARRAY_2_DB1ED0F23E314BAAADC4033B3F2DDBA3
