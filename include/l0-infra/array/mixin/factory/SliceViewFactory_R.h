//
// Created by Darwin Yuan on 2021/7/13.
//

#ifndef OBJECT_ARRAY_2_380A3A523FD14C7EB9710CA5B6B8DAEC
#define OBJECT_ARRAY_2_380A3A523FD14C7EB9710CA5B6B8DAEC

#include <l0-infra/array/view/SliceView.h>
#include <l0-infra/array/concept/Pred.h>

namespace mixin {
    template<typename T>
    struct SliceViewFactory_R : T {
        using typename T::SizeType;
        using typename T::ObjectType;
        using typename T::OffsetType;

    protected:
        using T::MakeSlice;
        using T::MakeFromSlice;
        using T::MakeUntilSlice;
        using typename T::ThisType;

    public:
        using T::Slice;
        using T::From;
        using T::Until;
        using T::Range;

        auto Slice(OffsetType from, OffsetType until) && -> auto {
            return T::template MakeSlice<false, true>(from, until);
        }

        auto Slice(OffsetType from, OffsetType until) const && -> auto {
            return T::template MakeSlice<true, true>(from, until);
        }

        auto From(OffsetType from) && -> auto {
            return std::move(*this).MakeFromSlice(T::ToIndex(from));
        }

        auto From(OffsetType from) const && -> auto {
            return std::move(*this).MakeFromSlice(T::ToIndex(from));
        }

        auto Until(OffsetType until) && -> auto {
            return std::move(*this).MakeUntilSlice(T::ToIndex(until));
        }

        auto Until(OffsetType until) const && -> auto {
            return std::move(*this).MakeUntilSlice(T::ToIndex(until));
        }

        template<__pRed_CoNcEpT(PRED)>
        auto Range(PRED&& pred) && -> auto {
            return T::MakeRange<false, true>(std::forward<PRED>(pred));
        }

        template<__pRed_CoNcEpT(PRED)>
        auto Range(PRED&& pred) const && -> auto {
            return T::MakeRange<true, true>(std::forward<PRED>(pred));
        }

        auto Range(ObjectType const& obj) && -> auto {
            return std::move(*this).Range([&](auto&& elem) { return elem == obj; });
        }

        auto Range(ObjectType const& obj) const&& -> auto {
            return std::move(*this).Range([&](auto&& elem) { return elem == obj; });
        }
    };
}

#endif //OBJECT_ARRAY_2_380A3A523FD14C7EB9710CA5B6B8DAEC
