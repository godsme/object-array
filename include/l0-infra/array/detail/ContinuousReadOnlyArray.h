////
//// Created by Darwin Yuan on 2021/6/24.
////
//
//#ifndef OBJECT_ARRAY_CONTINUOUSREADONLYARRAY_H
//#define OBJECT_ARRAY_CONTINUOUSREADONLYARRAY_H
//
//#include <l0-infra/array/detail/ReadOnlyArrayLike.h>
//
//namespace detail {
//    template<typename DATA_HOLDER, typename MIXINS, bool ORDERED=false>
//    class ContinuousReadOnlyArrayLike : public detail::ReadOnlyArrayLike<DATA_HOLDER, MIXINS, ORDERED> {
//        using Parent = detail::ReadOnlyArrayLike<DATA_HOLDER, MIXINS>;
//
//    protected:
//        using typename Parent::Mixins;
//
//    public:
//        using Parent::Parent;
//
////        using Mixins::FindIndexEx;
////        using Mixins::FindEx;
////        using Mixins::ExistsEx;
////
////        using Mixins::ForEachEx;
////
////        using Mixins::MinElemEx;
////        using Mixins::MaxElemEx;
////        using Mixins::MinElemIndexEx;
////        using Mixins::MaxElemIndexEx;
////
////        using Mixins::Scope;
////        using Mixins::Exclude;
//    };
//
//    template<typename DATA_HOLDER, typename MIXINS, bool ORDERED=false>
//    class ContinuousReadOnlyArray : public detail::ContinuousReadOnlyArrayLike<DATA_HOLDER, MIXINS, ORDERED> {
//        using Parent = detail::ContinuousReadOnlyArrayLike<DATA_HOLDER, MIXINS>;
//
//    protected:
//        using typename Parent::Mixins;
//
//    public:
//        using Parent::Parent;
//
////        using Mixins::GetNum;
////        using Mixins::Slice;
////        using Mixins::From;
////        using Mixins::Until;
//    };
//}
//
//#endif //OBJECT_ARRAY_CONTINUOUSREADONLYARRAY_H
