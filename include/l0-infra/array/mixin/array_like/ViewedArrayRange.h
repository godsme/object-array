//
// Created by Darwin Yuan on 2021/7/11.
//

#ifndef OBJECT_ARRAY_2_399B9BB9A6B145B49F0033176E725CD9
#define OBJECT_ARRAY_2_399B9BB9A6B145B49F0033176E725CD9

namespace mixin {
    template<typename T>
    struct ViewedArrayRange : T {
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

#endif //OBJECT_ARRAY_2_399B9BB9A6B145B49F0033176E725CD9
