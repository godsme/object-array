//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_RANGEDVIEWFACTORY_H
#define OBJECT_ARRAY_RANGEDVIEWFACTORY_H

#include <l0-infra/object-array/concept/RangedArrayLike.h>
#include <l0-infra/object-array/view/Slice.h>

namespace mixin {
    template<__cOnCePt(SimpleRangedArrayLike) T>
    struct RangedViewFactory : T {
        using Self = T;
    public:
        using typename T::SizeType;
        using typename T::ObjectType;
        using typename T::OffsetType;
        using typename T::EndOffsetType;
        using typename T::IndexedContainer;
        using typename T::DataHolder;

        using Self::IndexBegin;
        using Self::IndexEnd;

    private:
        struct Array : private DataHolder, IndexedContainer {
            using DataHolder::DataHolder;
            using IndexedContainer::GetObj;

            using typename DataHolder::SizeType;
            using typename DataHolder::ObjectType;
            using typename DataHolder::ElemType;

            constexpr static auto MAX_SIZE = DataHolder::MAX_SIZE;
            Array(Array&&) = default;
        };

    protected:
        auto MakeSlice(SizeType from, SizeType until) && -> auto {
            return view::ValueSlice<Array>{reinterpret_cast<Array&&>(*this), from, until};
        }

        auto MakeSlice(SizeType from, SizeType until) const && -> auto {
            return view::ValueSlice<Array const>{reinterpret_cast<Array const &&>(*this), from, until};
        }

    private:
        auto MakeSlice(SizeType from, SizeType until) & -> view::Slice<IndexedContainer> {
            return {static_cast<IndexedContainer&>(*this), from, until};
        }

        auto MakeSlice(SizeType from, SizeType until) const & -> view::Slice<IndexedContainer const> {
            return {static_cast<IndexedContainer const&>(*this), from, until};
        }

        template<bool CONST>
        auto GetThis() const -> auto* {
            if constexpr(CONST) {
                return this;
            } else {
                return ::detail::RemoveConstThis(this);
            }
        }

        template<bool CONST, bool R_VALUE>
        auto DoMakeSlice(SizeType from, SizeType until) const -> auto {
            if constexpr(R_VALUE) {
                return std::move(*GetThis<CONST>()).MakeSlice(from, until);
            } else {
                return GetThis<CONST>()->MakeSlice(from, until);
            }
        }

    protected:
        template<bool CONST, bool R_VALUE>
        auto MakeSliceByFrom(SizeType from, EndOffsetType until) const -> auto {
            auto until_ = until.ToIndex(IndexEnd());
            if(until_ <= from) {
                return DoMakeSlice<CONST, R_VALUE>(from, from);
            } else {
                return DoMakeSlice<CONST, R_VALUE>(from, until_);
            }
        }

        template<bool CONST, bool R_VALUE>
        auto MakeSlice(OffsetType from, EndOffsetType until) const -> auto {
            auto from_  = from.ToIndex(IndexEnd());
            if(from_ == IndexEnd()) {
                return DoMakeSlice<CONST, R_VALUE>(from_, from_);
            } else {
                return MakeSliceByFrom<CONST, R_VALUE>(from_, until);
            }
        }

    public:
        auto Slice(OffsetType, EndOffsetType) && -> void {}
        auto Slice(OffsetType, EndOffsetType) const && -> void {}

        auto Slice(OffsetType from, EndOffsetType until) & -> auto {
            return MakeSlice<false, false>(from, until);
        }

        auto Slice(OffsetType from, EndOffsetType until) const & -> auto {
            return MakeSlice<true, false>(from, until);
        }

        auto From(OffsetType) && -> void {}
        auto From(OffsetType) const && -> void {}

        auto From(OffsetType from) & -> auto {
            return MakeSlice(from.ToIndex(IndexEnd()), IndexEnd());
        }

        auto From(OffsetType from) const& -> auto {
            return MakeSlice(from.ToIndex(IndexEnd()), IndexEnd());
        }

        auto Until(EndOffsetType) && -> void {}
        auto Until(EndOffsetType) const && -> void {}

        auto Until(EndOffsetType until) & -> auto {
            return MakeSliceByFrom<false, false>(IndexBegin(), until);
        }

        auto Until(EndOffsetType until) const& -> auto {
            return MakeSliceByFrom<true, false>(IndexBegin(), until);
        }
    };
}

#endif //OBJECT_ARRAY_RANGEDVIEWFACTORY_H
