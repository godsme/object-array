//
// Created by Darwin Yuan on 2021/7/12.
//

#ifndef OBJECT_ARRAY_2_97B564B361B04A1E90BEEDD3E1B229A7
#define OBJECT_ARRAY_2_97B564B361B04A1E90BEEDD3E1B229A7


namespace mixin {
    template<typename T>
    struct ViewedRange : T {
        using typename T::SizeType;

    public:
        auto IndexBegin() const -> SizeType {
            return T::GetArray().IndexBegin();
        }
        auto IndexEnd() const -> SizeType {
            return T::GetArray().IndexEnd();
        }
    };
}

#endif //OBJECT_ARRAY_2_97B564B361B04A1E90BEEDD3E1B229A7
