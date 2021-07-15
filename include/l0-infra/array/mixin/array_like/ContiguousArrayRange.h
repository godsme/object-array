//
// Created by Darwin Yuan on 2021/7/9.
//

#ifndef OBJECT_ARRAY_2_CONTIGUOUSARRAYRANGE_05D5140BD9ED4A2AABF5583AAA3C692B
#define OBJECT_ARRAY_2_CONTIGUOUSARRAYRANGE_05D5140BD9ED4A2AABF5583AAA3C692B

namespace mixin {
    template<typename T>
    struct ContiguousArrayRange : T {
        using typename T::SizeType;

        auto IndexBegin() const -> SizeType {
            return 0;
        }

        auto IndexEnd() const -> SizeType {
            return T::Num();
        }
    };
}

#endif //OBJECT_ARRAY_2_CONTIGUOUSARRAYRANGE_05D5140BD9ED4A2AABF5583AAA3C692B
