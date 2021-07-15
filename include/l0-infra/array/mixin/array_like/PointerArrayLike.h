//
// Created by Darwin Yuan on 2021/7/13.
//

#ifndef OBJECT_ARRAY_2_87604E1B03654102A58A1E0790040A0A
#define OBJECT_ARRAY_2_87604E1B03654102A58A1E0790040A0A

namespace mixin {
    template<typename T>
    struct PointerArrayLike : T {
    protected:
        using T::This;

    public:
        auto Num() const -> typename T::SizeType {
            return This()->pointers.GetNum();
        }

        auto GetPointers() const -> decltype(auto) {
            return (This()->pointers);
        }

        auto GetPointers() -> decltype(auto) {
            return (This()->pointers);
        }
    };
}

#endif //OBJECT_ARRAY_2_87604E1B03654102A58A1E0790040A0A
