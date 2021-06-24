//
// Created by Darwin Yuan on 2021/6/23.
//

#ifndef OBJECT_ARRAY_RVALUERANGEDVIEWFACTORY_H
#define OBJECT_ARRAY_RVALUERANGEDVIEWFACTORY_H

#include <object-array/mixin/RangedViewFactory.h>

namespace mixin {
    template<_concept::SimpleRangedArrayLike T>
    struct RValueRangedViewFactory : RangedViewFactory<T> {
        using Self = RangedViewFactory<T>;
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

        auto MakeSlice(SizeType from, SizeType until) const && -> auto {
            return view::ValueSlice<Array const>{reinterpret_cast<Array const &&>(*this), from, until};
        }

    public:
        using Self::Slice;
        using Self::From;
        using Self::Until;

        auto Slice(OffsetType from, EndOffsetType until) && -> auto {
            return std::move(*this).MakeSlice(from.ToIndex(IndexEnd()), until.ToIndex(IndexEnd()));
        }

        auto Slice(OffsetType from, EndOffsetType until) const && -> auto {
            return std::move(*this).MakeSlice(from.ToIndex(IndexEnd()), until.ToIndex(IndexEnd()));
        }

        auto From(OffsetType from) && -> auto {
            return std::move(*this).MakeSlice(from.ToIndex(IndexEnd()), IndexEnd());
        }

        auto From(OffsetType from) const && -> auto {
            return std::move(*this).MakeSlice(from.ToIndex(IndexEnd()), IndexEnd());
        }

        auto Until(EndOffsetType until) && -> auto {
            return std::move(*this).MakeSlice(IndexBegin(), until.ToIndex(IndexEnd()));
        }

        auto Until(EndOffsetType until) const && -> auto {
            return std::move(*this).MakeSlice(IndexBegin(), until.ToIndex(IndexEnd()));
        }
    };
}

#endif //OBJECT_ARRAY_RVALUERANGEDVIEWFACTORY_H
