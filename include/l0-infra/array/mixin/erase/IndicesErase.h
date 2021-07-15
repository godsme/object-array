//
// Created by Darwin Yuan on 2021/7/13.
//

#ifndef OBJECT_ARRAY_2_DF81B95B563B4F809B614E308C3017AD
#define OBJECT_ARRAY_2_DF81B95B563B4F809B614E308C3017AD

namespace mixin {
    template<typename T>
    struct IndicesErase : T {
        using typename T::SizeType;

    public:
        auto Erase(SizeType i) -> void {
            SizeType* index = T::GetIndices().At(i);
            if(index != nullptr) {
                T::GetArray().Erase(*index);
                T::GetIndices().Erase(i);
            }
        }
    };
}

#endif //OBJECT_ARRAY_2_DF81B95B563B4F809B614E308C3017AD
