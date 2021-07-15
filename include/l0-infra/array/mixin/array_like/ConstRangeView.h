//
// Created by Darwin Yuan on 2021/7/9.
//

#ifndef OBJECT_ARRAY_2_CONSTRANGEVIEW_3D7C2CEDE40D4C9C8D53EE465304D4B0
#define OBJECT_ARRAY_2_CONSTRANGEVIEW_3D7C2CEDE40D4C9C8D53EE465304D4B0

namespace mixin {
    template<typename T>
    struct ConstRangeView : T {
        using typename T::SizeType;

    private:
        using T::This;

    public:
        auto IndexBegin() const -> SizeType {
            return This()->RangeBegin();
        }

        auto IndexEnd() const -> SizeType {
            return This()->RangeEnd();
        }
    };
}

#endif //OBJECT_ARRAY_2_CONSTRANGEVIEW_3D7C2CEDE40D4C9C8D53EE465304D4B0
