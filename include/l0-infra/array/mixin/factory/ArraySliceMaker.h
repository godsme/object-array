//
// Created by Darwin Yuan on 2021/7/11.
//

#ifndef OBJECT_ARRAY_2_4C95EC8714F8437684EE9E316B4EC61B
#define OBJECT_ARRAY_2_4C95EC8714F8437684EE9E316B4EC61B

#include <l0-infra/array/view/SliceView.h>

namespace mixin {
    template<typename T>
    struct ArraySliceMaker : T {
        using typename T::SizeType;

    protected:
        using typename T::ThisType;

    public:
        auto MakeSlice(SizeType from, SizeType until) & -> RefSliceView<ThisType> {
            return {T::ToThisType(), from, until};
        }

        auto MakeSlice(SizeType num) & -> RefSliceView<ThisType> {
            return {T::ToThisType(), 0, num};
        }

        auto MakeSlice(SizeType from, SizeType until) const & -> RefSliceView<ThisType const> {
            return {T::ToThisType(), from, until};
        }

        auto MakeSlice(SizeType from, SizeType until) && -> ValueSliceView<ThisType> {
            return {T::ToThisType(), from, until};
        }

        auto MakeSlice(SizeType from, SizeType until) const && -> ValueSliceView<ThisType const> {
            return {T::ToThisType(), from, until};
        }

        auto MakeSlice(SizeType num) && -> ValueSliceView<ThisType> {
            return {T::ToThisType(), 0, num};
        }
    };
}

#endif //OBJECT_ARRAY_2_4C95EC8714F8437684EE9E316B4EC61B
