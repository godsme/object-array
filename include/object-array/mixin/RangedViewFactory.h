//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_RANGEDVIEWFACTORY_H
#define OBJECT_ARRAY_RANGEDVIEWFACTORY_H

#include <object-array/mixin/detail/DefMixin.h>
#include <object-array/concept/RangedArrayLike.h>
#include <object-array/view/Slice.h>

namespace mixin {
    template<_concept::SimpleRangedArrayLike T>
    struct RangedViewFactory : detail::Extends<T> {
        using Self = detail::Extends<T>;
    public:
        using SizeType = typename T::SizeType;
        using ObjectType = typename T::ObjectType;
        using OffsetType = typename T::OffsetType;
        using EndOffsetType = typename T::EndOffsetType;
        using IndexedContainer = typename T::IndexedContainer;
        using DataHolder = typename T::DataHolder;

        using Self::IndexBegin;
        using Self::IndexEnd;

    private:
        struct Array : private DataHolder, IndexedContainer {
            using DataHolder::DataHolder;
            using IndexedContainer::GetObj;
            using SizeType = typename DataHolder::SizeType;
            using ObjectType = typename DataHolder::ObjectType;
            using ElemType = typename DataHolder::ElemType;
            constexpr static auto MAX_SIZE = DataHolder::MAX_SIZE;
            Array(Array&&) = default;
        };

    private:
        auto MakeSlice(SizeType from, SizeType until) && -> auto {
            return view::ValueSlice<Array>{reinterpret_cast<Array&&>(*this), from, until};
        }

        auto MakeSlice(SizeType from, SizeType until) & -> auto {
            return view::Slice<IndexedContainer>{static_cast<IndexedContainer&>(*this), from, until};
        }

        auto MakeSlice(SizeType from, SizeType until) const & -> auto {
            return view::Slice<IndexedContainer const>{static_cast<IndexedContainer const&>(*this), from, until};
        }

    public:
        auto Slice(OffsetType from, EndOffsetType until) && -> auto {
            return std::move(*this).MakeSlice(from.ToIndex(IndexEnd()), until.ToIndex(IndexEnd()));
        }

        auto Slice(OffsetType from, EndOffsetType until) & -> auto {
            return MakeSlice(from.ToIndex(IndexEnd()), until.ToIndex(IndexEnd()));
        }

        auto Slice(OffsetType from, EndOffsetType until) const & -> auto {
            return MakeSlice(from.ToIndex(IndexEnd()), until.ToIndex(IndexEnd()));
        }

        auto From(OffsetType from) && -> auto {
            return std::move(*this).MakeSlice(from.ToIndex(IndexEnd()), IndexEnd());
        }

        auto From(OffsetType from) & -> auto {
            return MakeSlice(from.ToIndex(IndexEnd()), IndexEnd());
        }

        auto From(OffsetType from) const& -> auto {
            return MakeSlice(from.ToIndex(IndexEnd()), IndexEnd());
        }

        auto Until(EndOffsetType until) && -> auto {
            return std::move(*this).MakeSlice(IndexBegin(), until.ToIndex(IndexEnd()));
        }

        auto Until(EndOffsetType until) & -> auto {
            return MakeSlice(IndexBegin(), until.ToIndex(IndexEnd()));
        }

        auto Until(EndOffsetType until) const& -> auto {
            return MakeSlice(IndexBegin(), until.ToIndex(IndexEnd()));
        }
    };
}

#endif //OBJECT_ARRAY_RANGEDVIEWFACTORY_H
