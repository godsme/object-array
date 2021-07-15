//
// Created by Darwin Yuan on 2021/7/11.
//

#ifndef OBJECT_ARRAY_2_04E4C8F3017941799A9915ED05298E39
#define OBJECT_ARRAY_2_04E4C8F3017941799A9915ED05298E39

namespace mixin {
    template<typename T>
    struct ScopeCleanUp : T {
        using typename T::BitMap;

    public:
        auto CleanUp(BitMap scope) -> void {
            if(T::Num() == 0) return;
            for(auto i=T::Num()-1; i>=0; --i) {
                if(scope[i]) T::Erase(i);
            }
        }

        auto CleanUpEx(BitMap excluded) -> void {
            CleanUp(~excluded);
        }
    };
}

#endif //OBJECT_ARRAY_2_04E4C8F3017941799A9915ED05298E39
