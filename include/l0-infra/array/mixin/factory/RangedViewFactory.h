//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_RANGEDVIEWFACTORY_H
#define OBJECT_ARRAY_RANGEDVIEWFACTORY_H

#include <l0-infra/array/concept/RangedArrayLike.h>
#include <l0-infra/array/view/Slice.h>

namespace mixin {
    template<__cOnCePt(SimpleRangedArrayLike) T>
    class RangedViewFactory : public T {
        using Self = T;

    public:
        using typename T::SizeType;
        using typename T::ObjectType;
        using typename T::OffsetType;

    protected:
        using typename T::RangedArrayLike;
        using typename T::DataHolder;

        using Self::IndexBegin;
        using Self::IndexEnd;

    protected:
        using Array = detail::ValueRangedArray<DataHolder, RangedArrayLike>;
        using Self::IS_ORDERED;

    protected:
        auto MakeSlice(SizeType from, SizeType until) && -> view::ValueSlice<Array, IS_ORDERED> {
            return {reinterpret_cast<Array&&>(*this), from, until};
        }

        auto MakeSlice(SizeType from, SizeType until) const && -> view::ValueSlice<Array const, IS_ORDERED> {
            return {reinterpret_cast<Array const &&>(*this), from, until};
        }

        auto MakeFromSlice(SizeType from) && -> view::ValueFromView<Array, IS_ORDERED> {
            return {reinterpret_cast<Array&&>(*this), from};
        }

        auto MakeFromSlice(SizeType from) const && -> view::ValueFromView<Array const, IS_ORDERED> {
            return {reinterpret_cast<Array const &&>(*this), from};
        }

        auto MakeUntilSlice(SizeType until) && -> view::ValueUntilView<Array, IS_ORDERED> {
            return {reinterpret_cast<Array&&>(*this), until};
        }

        auto MakeUntilSlice(SizeType until) const && -> view::ValueUntilView<Array const, IS_ORDERED> {
            return {reinterpret_cast<Array const &&>(*this), until};
        }

    private:
        auto MakeSlice(SizeType from, SizeType until) & -> view::Slice<RangedArrayLike, IS_ORDERED> {
            return {static_cast<RangedArrayLike&>(*this), from, until};
        }

        auto MakeSlice(SizeType from, SizeType until) const & -> view::Slice<RangedArrayLike const, IS_ORDERED> {
            return {static_cast<RangedArrayLike const&>(*this), from, until};
        }

        auto MakeFromSlice(SizeType from) & -> view::FromView<RangedArrayLike, IS_ORDERED> {
            return {static_cast<RangedArrayLike&>(*this), from};
        }

        auto MakeFromSlice(SizeType from) const & -> view::FromView<RangedArrayLike const, IS_ORDERED> {
            return {static_cast<RangedArrayLike const&>(*this), from};
        }

        auto MakeUntilSlice(SizeType until) & -> view::UntilView<RangedArrayLike, IS_ORDERED> {
            return {static_cast<RangedArrayLike&>(*this), until};
        }

        auto MakeUntilSlice(SizeType until) const & -> view::UntilView<RangedArrayLike const, IS_ORDERED> {
            return {static_cast<RangedArrayLike const&>(*this), until};
        }

        template<bool AS_CONST>
        auto GetThis() const -> auto* {
            if constexpr(AS_CONST) {
                return this;
            } else {
                return ::detail::RemoveConstThis(this);
            }
        }

        template<bool AS_CONST, bool R_VALUE>
        auto DoMakeSlice(SizeType from, SizeType until) const -> auto {
            if constexpr(R_VALUE) {
                return std::move(*GetThis<AS_CONST>()).MakeSlice(from, until);
            } else {
                return GetThis<AS_CONST>()->MakeSlice(from, until);
            }
        }

    protected:
        template<bool AS_CONST, bool R_VALUE>
        auto MakeSliceByFrom(SizeType from, OffsetType until) const -> auto {
            auto until_ = until.ToIndex(IndexEnd());
            if(until_ <= from) {
                return DoMakeSlice<AS_CONST, R_VALUE>(from, from);
            } else {
                return DoMakeSlice<AS_CONST, R_VALUE>(from, until_);
            }
        }

        template<bool AS_CONST, bool R_VALUE>
        auto MakeSlice(OffsetType from, OffsetType until) const -> auto {
            auto from_  = from.ToIndex(IndexEnd());
            if(from_ == IndexEnd()) {
                return DoMakeSlice<AS_CONST, R_VALUE>(from_, from_);
            } else {
                return MakeSliceByFrom<AS_CONST, R_VALUE>(from_, until);
            }
        }

    public:
        auto Slice(OffsetType, OffsetType) && -> void {}
        auto Slice(OffsetType, OffsetType) const && -> void {}

        auto Slice(OffsetType from, OffsetType until) & -> auto {
            return MakeSlice<false, false>(from, until);
        }

        auto Slice(OffsetType from, OffsetType until) const & -> auto {
            return MakeSlice<true, false>(from, until);
        }

        auto From(OffsetType) && -> void {}
        auto From(OffsetType) const && -> void {}

        auto From(OffsetType from) & -> auto {
            return MakeFromSlice(from.ToIndex(IndexEnd()));
        }

        auto From(OffsetType from) const& -> auto {
            return MakeFromSlice(from.ToIndex(IndexEnd()));
        }

        auto Until(OffsetType) && -> void {}
        auto Until(OffsetType) const && -> void {}

        auto Until(OffsetType until) & -> auto {
            return MakeUntilSlice(until.ToIndex(IndexEnd()));
        }

        auto Until(OffsetType until) const& -> auto {
            return MakeUntilSlice(until.ToIndex(IndexEnd()));
        }
    };
}

#endif //OBJECT_ARRAY_RANGEDVIEWFACTORY_H
