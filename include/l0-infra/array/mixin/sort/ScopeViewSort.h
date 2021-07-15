//
// Created by Darwin Yuan on 2021/7/12.
//

#ifndef OBJECT_ARRAY_2_95B55795A3FD457AAB4A8E61FD883C6B
#define OBJECT_ARRAY_2_95B55795A3FD457AAB4A8E61FD883C6B

#include <l0-infra/array/concept/Less.h>

namespace mixin {
    template<typename T>
    struct ScopeViewSort : T {
        using typename T::ObjectType;
        using typename T::SizeType;

    protected:
        using typename T::ThisType;
        using typename T::ArrayType;

    public:
        template<__lEsS_cOnCePt(LESS)>
        auto DoSort(LESS&& less) -> void {
            T::GetArray().Unsafe_ScopeSort(T::GetScope(), std::forward<LESS>(less));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto DoStableSort(LESS&& less) -> void {
            T::GetArray().Unsafe_ScopeStableSort(T::GetScope(), std::forward<LESS>(less));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto DoPartialSort(LESS&& less, SizeType n) -> SizeType {
            return T::GetArray().Unsafe_ScopePartialSort(T::GetScope(), std::forward<LESS>(less), n);
        }
    };
}

#endif //OBJECT_ARRAY_2_95B55795A3FD457AAB4A8E61FD883C6B
