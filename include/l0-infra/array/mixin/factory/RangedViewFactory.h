//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_RANGEDVIEWFACTORY_H
#define OBJECT_ARRAY_RANGEDVIEWFACTORY_H

#include <l0-infra/array/concept/RangedArrayLike.h>
#include <l0-infra/array/view/Slice.h>
#include <l0-infra/array/mixin/factory/InternalRangedViewFactory.h>

namespace mixin {
    template<__cOnCePt(SimpleRangedArrayLike) T>
    class RangedViewFactory : public InternalRangedViewFactory<T> {
        using Self = InternalRangedViewFactory<T>;

    public:
        using typename T::SizeType;
        using typename T::ObjectType;
        using typename T::OffsetType;

    protected:
        using Self::IndexBegin;
        using Self::IndexEnd;
        using typename Self::Array;

    protected:
        using Self::IS_ORDERED;

    protected:
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

    protected:
        template<bool AS_CONST, bool R_VALUE>
        auto MakeSliceByFrom(SizeType from, OffsetType until) const -> auto {
            auto until_ = until.ToIndex(IndexEnd());
            if(until_ <= from) {
                return Self::template DoMakeSlice<AS_CONST, R_VALUE, IS_ORDERED>(from, from);
            } else {
                return Self::template DoMakeSlice<AS_CONST, R_VALUE, IS_ORDERED>(from, until_);
            }
        }

        template<bool AS_CONST, bool R_VALUE>
        auto MakeSlice(OffsetType from, OffsetType until) const -> auto {
            auto from_  = from.ToIndex(IndexEnd());
            if(from_ == IndexEnd()) {
                return Self::template DoMakeSlice<AS_CONST, R_VALUE, IS_ORDERED>(from_, from_);
            } else {
                return MakeSliceByFrom<AS_CONST, R_VALUE>(from_, until);
            }
        }

    public:
        auto Slice(OffsetType, OffsetType) && -> void = delete;
        auto Slice(OffsetType, OffsetType) const && -> void = delete;

        auto Slice(OffsetType from, OffsetType until) & -> auto {
            return MakeSlice<false, false>(from, until);
        }

        auto Slice(OffsetType from, OffsetType until) const & -> auto {
            return MakeSlice<true, false>(from, until);
        }

        auto From(OffsetType) && -> void = delete;
        auto From(OffsetType) const && -> void = delete;

        auto From(OffsetType from) & -> auto {
            return Self::template MakeFromSlice<IS_ORDERED>(from.ToIndex(IndexEnd()));
        }

        auto From(OffsetType from) const& -> auto {
            return Self::template MakeFromSlice<IS_ORDERED>(from.ToIndex(IndexEnd()));
        }

        auto Until(OffsetType) && -> void = delete;
        auto Until(OffsetType) const && -> void = delete;

        auto Until(OffsetType until) & -> auto {
            return Self::template MakeUntilSlice<IS_ORDERED>(until.ToIndex(IndexEnd()));
        }

        auto Until(OffsetType until) const& -> auto {
            return Self::template MakeUntilSlice<IS_ORDERED>(until.ToIndex(IndexEnd()));
        }
    };
}

#endif //OBJECT_ARRAY_RANGEDVIEWFACTORY_H
