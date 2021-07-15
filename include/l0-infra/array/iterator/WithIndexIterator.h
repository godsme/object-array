//
// Created by Darwin Yuan on 2021/7/10.
//

#ifndef OBJECT_ARRAY_2_E2AFA90128D6471F95BBFC2E3D552837
#define OBJECT_ARRAY_2_E2AFA90128D6471F95BBFC2E3D552837

#include <l0-infra/array/iterator/Iterator.h>
#include <l0-infra/array/iterator/detail/WithIndexIterator.h>
#include <l0-infra/base/detail/CondConst.h>
#include <l0-infra/array/iterator/detail/IndexIterator.h>

namespace iterator {
    template<typename ARRAY, typename OBJ_TYPE>
    struct WithIndexIterator : detail::ByIndexWithIndexIterator<ARRAY, OBJ_TYPE> {
        using Parent = detail::ByIndexWithIndexIterator<ARRAY, OBJ_TYPE>;
        using Parent::Parent;
        auto operator++() -> WithIndexIterator& {
            Parent::StepForward();
            return *this;
        }
    };

    template<typename ARRAY>
    WithIndexIterator(ARRAY&, typename ARRAY::SizeType) -> WithIndexIterator<ARRAY, ::detail::CondConst_t<std::is_const_v<ARRAY>, typename ARRAY::ObjectType>>;
}

#endif //OBJECT_ARRAY_2_E2AFA90128D6471F95BBFC2E3D552837
