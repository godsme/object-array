//
// Created by Darwin Yuan on 2021/7/9.
//

#ifndef OBJECT_ARRAY_2_VIEWEDARRAY_C516BD87522F4CFA85729B2BD9859078
#define OBJECT_ARRAY_2_VIEWEDARRAY_C516BD87522F4CFA85729B2BD9859078

#include <l0-infra/base/InvokeConstMethod.h>

namespace mixin {
    template<typename T>
    struct ViewedArray : T {
        using typename T::SizeType;

    protected:
        using T::This;
        using typename T::DataHolder;
        using ArrayType = typename DataHolder::ArrayType;

    public:
        auto GetArray() const -> decltype(auto) {
            return This()->GetArray();
        }

        auto GetArray() -> decltype(auto) {
            return This()->GetArray();
        }

        template<bool TO_NON_CONST>
        auto GetArray() const -> decltype(auto) {
            if constexpr(TO_NON_CONST) {
                return ::detail::RemoveConstThis(this)->GetArray();
            } else {
                return GetArray();
            }
        }
    };
}

#endif //OBJECT_ARRAY_2_VIEWEDARRAY_C516BD87522F4CFA85729B2BD9859078
