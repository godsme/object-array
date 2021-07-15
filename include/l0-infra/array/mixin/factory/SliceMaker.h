//
// Created by Darwin Yuan on 2021/7/11.
//

#ifndef OBJECT_ARRAY_2_910C0E2519AE46AA9555CF72FB3A1FA0
#define OBJECT_ARRAY_2_910C0E2519AE46AA9555CF72FB3A1FA0

namespace mixin {
    template<typename T>
    struct SliceMaker : T {
        using typename T::SizeType;

    protected:
        using typename T::ThisType;

    public:
        auto MakeSlice(SizeType num) -> ThisType {
            return {T::GetArray(), T::IndexBegin(), T::IndexBegin() + num};
        }
    };
}

#endif //OBJECT_ARRAY_2_910C0E2519AE46AA9555CF72FB3A1FA0
