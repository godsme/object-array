//
// Created by Darwin Yuan on 2021/7/8.
//

#ifndef OBJECT_ARRAY_INTERNALRANGEDVIEWFACTORY_H
#define OBJECT_ARRAY_INTERNALRANGEDVIEWFACTORY_H

#include <l0-infra/array/concept/RangedArrayLike.h>
#include <l0-infra/array/view/Slice.h>

namespace mixin {
    template<typename T>
    class InternalRangedViewFactory : public T {
        using Self = T;

    public:
        using typename T::SizeType;
        using typename T::ObjectType;

    protected:
        using typename T::RangedArrayLike;
        using typename T::DataHolder;

        using Self::IndexBegin;
        using Self::IndexEnd;

    protected:
        using Array = detail::ValueRangedArray<DataHolder, RangedArrayLike>;

    protected:
        template<bool ORDERED>
        auto MakeSlice(SizeType from, SizeType until) && -> view::ValueSlice<Array, ORDERED> {
            return {reinterpret_cast<Array&&>(*this), from, until};
        }

        template<bool ORDERED>
        auto MakeSlice(SizeType from, SizeType until) const && -> view::ValueSlice<Array const, ORDERED> {
            return {reinterpret_cast<Array const &&>(*this), from, until};
        }

    private:
        template<bool ORDERED>
        auto MakeSlice(SizeType from, SizeType until) & -> view::Slice<RangedArrayLike, ORDERED> {
            return {static_cast<RangedArrayLike&>(*this), from, until};
        }

        template<bool ORDERED>
        auto MakeSlice(SizeType from, SizeType until) const & -> view::Slice<RangedArrayLike const, ORDERED> {
            return {static_cast<RangedArrayLike const&>(*this), from, until};
        }

        template<bool AS_CONST>
        auto GetThis() const -> auto* {
            if constexpr(AS_CONST) {
                return this;
            } else {
                return ::detail::RemoveConstThis(this);
            }
        }

    protected:
        template<bool AS_CONST, bool R_VALUE, bool ORDERED>
        auto DoMakeSlice(SizeType from, SizeType until) const -> auto {
            if constexpr(R_VALUE) {
                return std::move(*GetThis<AS_CONST>()).template MakeSlice<ORDERED>(from, until);
            } else {
                return GetThis<AS_CONST>()->template MakeSlice<ORDERED>(from, until);
            }
        }

        template<bool ORDERED>
        auto MakeFromSlice(SizeType from) & -> view::FromView<RangedArrayLike, ORDERED> {
            return {static_cast<RangedArrayLike&>(*this), from};
        }

        template<bool ORDERED>
        auto MakeFromSlice(SizeType from) const & -> view::FromView<RangedArrayLike const, ORDERED> {
            return {static_cast<RangedArrayLike const&>(*this), from};
        }

        template<bool ORDERED>
        auto MakeUntilSlice(SizeType until) & -> view::UntilView<RangedArrayLike, ORDERED> {
            return {static_cast<RangedArrayLike&>(*this), until};
        }

        template<bool ORDERED>
        auto MakeUntilSlice(SizeType until) const & -> view::UntilView<RangedArrayLike const, ORDERED> {
            return {static_cast<RangedArrayLike const&>(*this), until};
        }

    };
}

#endif //OBJECT_ARRAY_INTERNALRANGEDVIEWFACTORY_H
