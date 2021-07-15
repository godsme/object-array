//
// Created by Darwin Yuan on 2021/7/13.
//

#ifndef OBJECT_ARRAY_2_0FE320F7799949D7BBC48482465667A4
#define OBJECT_ARRAY_2_0FE320F7799949D7BBC48482465667A4

namespace mixin {
    template<typename T>
    struct DynamicRangedClear : T {
        using typename T::SizeType;

    protected:
        using T::This;

        auto DoClearFrom(SizeType from) -> void {
            Unsafe_Clear(from, T::Num());
        }

    public:
        auto Unsafe_Clear(SizeType from, SizeType until) -> void {
            if(from >= until) return;
            for(int i=until-1; i >= from; --i) {
                T::Erase(i);
            }
        }

        auto Clear() -> void {
            This()->DoClear();
        }
    };
}

#endif //OBJECT_ARRAY_2_0FE320F7799949D7BBC48482465667A4
