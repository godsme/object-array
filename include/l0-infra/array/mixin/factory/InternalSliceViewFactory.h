////
//// Created by Darwin Yuan on 2021/7/11.
////
//
//#ifndef OBJECT_ARRAY_2_8D3C97E9396244BBBDB1AA15F836FCB3
//#define OBJECT_ARRAY_2_8D3C97E9396244BBBDB1AA15F836FCB3
//
//#include <l0-infra/array/view/SliceView.h>
//
//namespace mixin {
//    template<typename T>
//    struct InternalSliceViewFactory : T {
//        using typename T::SizeType;
//
//    protected:
//        using T::MakeSlice;
//
//    protected:
//        using typename T::ThisType;
//
//    private:
//        template<bool AS_CONST>
//        auto GetThis() const -> auto* {
//            if constexpr(AS_CONST) {
//                return this;
//            } else {
//                return ::detail::RemoveConstThis(this);
//            }
//        }
//
//    protected:
//        template<bool AS_CONST, bool R_VALUE>
//        auto DoMakeSlice(SizeType from, SizeType until) const -> auto {
//            if constexpr(R_VALUE) {
//                return std::move(*GetThis<AS_CONST>()).template MakeSlice(from, until);
//            } else {
//                return GetThis<AS_CONST>()->template MakeSlice(from, until);
//            }
//        }
//
//        auto MakeFromSlice(SizeType from) & -> RefFromSliceView<ThisType> {
//            return {T::ToThisType(), from};
//        }
//
//        auto MakeFromSlice(SizeType from) const & -> RefFromSliceView<ThisType const> {
//            return {T::ToThisType(), from};
//        }
//
//        auto MakeUntilSlice(SizeType until) & -> RefUntilSliceView<ThisType> {
//            return {T::ToThisType(), until};
//        }
//
//        auto MakeUntilSlice(SizeType until) const & -> RefUntilSliceView<ThisType const> {
//            return {T::ToThisType(), until};
//        }
//    };
//}
//
//#endif //OBJECT_ARRAY_2_8D3C97E9396244BBBDB1AA15F836FCB3
