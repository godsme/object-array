//
// Created by Darwin Yuan on 2021/7/13.
//

#ifndef OBJECT_ARRAY_2_F0B83572D69A426D8E270E78EF9044E7
#define OBJECT_ARRAY_2_F0B83572D69A426D8E270E78EF9044E7


namespace mixin {
    template<typename T>
    struct IndicesRangedClear : T {
        using typename T::SizeType;

    protected:
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
            T::GetArray().Clear();
            T::GetIndices().Clear();
        }
    };
}

#endif //OBJECT_ARRAY_2_F0B83572D69A426D8E270E78EF9044E7
