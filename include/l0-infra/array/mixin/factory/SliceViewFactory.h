//
// Created by Darwin Yuan on 2021/7/11.
//

#ifndef OBJECT_ARRAY_2_2DD5353E6D5B4CE28D7079F1A67A1177
#define OBJECT_ARRAY_2_2DD5353E6D5B4CE28D7079F1A67A1177

#include <l0-infra/array/view/SliceView.h>
#include <l0-infra/array/concept/Pred.h>

namespace mixin {
    template<typename T>
    struct SliceViewFactory : T {
        using typename T::SizeType;
        using typename T::ObjectType;
        using typename T::OffsetType;

    protected:
        using T::MakeSlice;
        using typename T::ThisType;

    private:
        template<bool AS_CONST>
        auto GetThis() const -> auto* {
            if constexpr(AS_CONST) {
                return this;
            } else {
                return ::detail::RemoveConstThis(this);
            }
        }

    protected:
        auto ToIndex(OffsetType offset) const -> SizeType {
            return offset.ToIndex(T::Num());
        }

    protected:
        template<bool AS_CONST, bool R_VALUE>
        auto DoMakeSlice(SizeType from, SizeType until) const -> auto {
            if constexpr(R_VALUE) {
                return std::move(*GetThis<AS_CONST>()).MakeSlice(from, until);
            } else {
                return GetThis<AS_CONST>()->MakeSlice(from, until);
            }
        }

        auto MakeFromSlice(SizeType from) & -> RefFromSliceView<ThisType> {
            return {T::ToThisType(), from};
        }

        auto MakeFromSlice(SizeType from) const & -> RefFromSliceView<ThisType const> {
            return {T::ToThisType(), from};
        }

        auto MakeUntilSlice(SizeType until) & -> RefUntilSliceView<ThisType> {
            return {T::ToThisType(), until};
        }

        auto MakeUntilSlice(SizeType until) const & -> RefUntilSliceView<ThisType const> {
            return {T::ToThisType(), until};
        }

        template<__pRed_CoNcEpT(PRED)>
        auto FindRangeEnd(SizeType begin, PRED&& pred) const -> SizeType {
            auto end = begin+1;
            for(; end < T::Num(); ++end) {
                if constexpr(__wItH_iNdEx_pReD(PRED)) {
                    if (!pred(T::GetObject(end), end)) break;
                } else {
                    if (!pred(T::GetObject(end))) break;
                }
            }
            return end;
        }

    protected:
        template<bool AS_CONST, bool R_VALUE>
        auto MakeSliceByFrom(SizeType from, OffsetType until) const -> auto {
            auto until_ = ToIndex(until);
            if(until_ <= from) {
                return DoMakeSlice<AS_CONST, R_VALUE>(from, from);
            } else {
                return DoMakeSlice<AS_CONST, R_VALUE>(from, until_);
            }
        }

        template<bool AS_CONST, bool R_VALUE>
        auto MakeSlice(OffsetType from, OffsetType until) const -> auto {
            auto from_  = ToIndex(from);
            if(from_ == T::Num()) {
                return DoMakeSlice<AS_CONST, R_VALUE>(from_, from_);
            } else {
                return MakeSliceByFrom<AS_CONST, R_VALUE>(from_, until);
            }
        }

        template<bool AS_CONST, bool R_VALUE, __pRed_CoNcEpT(PRED)>
        auto MakeRange(PRED&& pred) const -> auto {
            auto [begin, end] = T::FindRange(pred);
            return DoMakeSlice<AS_CONST, R_VALUE>(begin, end);
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
            return MakeFromSlice(ToIndex(from));
        }

        auto From(OffsetType from) const& -> auto {
            return MakeFromSlice(ToIndex(from));
        }

        auto Until(OffsetType) && -> void = delete;
        auto Until(OffsetType) const && -> void = delete;

        auto Until(OffsetType until) & -> auto {
            return MakeUntilSlice(ToIndex(until));
        }

        auto Until(OffsetType until) const& -> auto {
            return MakeUntilSlice(ToIndex(until));
        }

        template<__pRed_CoNcEpT(PRED)>
        auto Range(PRED&& pred) && = delete;

        template<__pRed_CoNcEpT(PRED)>
        auto Range(PRED&& pred) const && = delete;

        auto Range(ObjectType const& obj) && = delete;
        auto Range(ObjectType const& obj) const&& = delete;

        template<__pRed_CoNcEpT(PRED)>
        auto Range(PRED&& pred) & -> auto {
            return MakeRange<false, false>(std::forward<PRED>(pred));
        }

        template<__pRed_CoNcEpT(PRED)>
        auto Range(PRED&& pred) const & -> auto {
            return MakeRange<true, false>(std::forward<PRED>(pred));
        }

        auto Range(ObjectType const& obj) & -> auto {
            return Range([&](auto&& elem) { return elem == obj; });
        }

        auto Range(ObjectType const& obj) const & -> auto {
            return Range([&](auto&& elem) { return elem == obj; });
        }
    };
}

#endif //OBJECT_ARRAY_2_2DD5353E6D5B4CE28D7079F1A67A1177
