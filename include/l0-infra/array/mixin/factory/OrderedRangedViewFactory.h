//
// Created by Darwin Yuan on 2021/7/8.
//

#ifndef OBJECT_ARRAY_ORDEREDRANGEDVIEWFACTORY_H
#define OBJECT_ARRAY_ORDEREDRANGEDVIEWFACTORY_H

#include <l0-infra/array/concept/RangedArrayLike.h>
#include <l0-infra/array/view/Slice.h>

namespace mixin {
    template<typename T>
    class OrderedRangedViewFactory : public T {
        using Self = T;

    public:
        using typename T::SizeType;
        using typename T::ObjectType;

    protected:
        using typename T::RangedArrayLike;
        using typename T::DataHolder;

        using Self::IndexBegin;
        using Self::IndexEnd;
        using Self::GetLess;

    protected:
        using Array = detail::ValueRangedArray<DataHolder, RangedArrayLike>;

    protected:
        auto MakeSlice(SizeType from, SizeType until) && -> view::ValueSlice<Array, false> {
            return {reinterpret_cast<Array&&>(*this), from, until};
        }

        auto MakeSlice(SizeType from, SizeType until) const && -> view::ValueSlice<Array const, false> {
            return {reinterpret_cast<Array const &&>(*this), from, until};
        }

    private:
        auto MakeSlice(SizeType from, SizeType until) & -> view::Slice<RangedArrayLike, false> {
            return {static_cast<RangedArrayLike&>(*this), from, until};
        }

        auto MakeSlice(SizeType from, SizeType until) const & -> view::Slice<RangedArrayLike const, false> {
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

        template<bool AS_CONST, bool R_VALUE>
        auto DoMakeSlice(SizeType from, SizeType until) const -> auto {
            if constexpr(R_VALUE) {
                return std::move(*GetThis<AS_CONST>()).MakeSlice(from, until);
            } else {
                return GetThis<AS_CONST>()->MakeSlice(from, until);
            }
        }

    protected:
        template<bool AS_CONST, bool R_VALUE, typename PRED>
        auto MakeSlice(PRED&& pred) const -> auto {
            auto from = Self::FindIndex(std::forward<PRED>(pred));
            if(!from) {
                return DoMakeSlice<AS_CONST, R_VALUE>(IndexEnd(), IndexEnd());
            } else {
                SizeType until = *from;
                for(; until<IndexEnd(); until++) {
                    if(!pred(Self::GetObj(until))) break;
                }
                return DoMakeSlice<AS_CONST, R_VALUE>(*from, until);
            }
        }

        template<bool AS_CONST, bool R_VALUE>
        auto MakeSlice(ObjectType const& obj) const -> auto {
            return MakeSlice<AS_CONST, R_VALUE>([&obj, &less = GetLess()] (auto&& elem) {
                return !(less(elem, obj) || less(obj, elem));
            });
        }

    public:
        auto Range(ObjectType const&) && -> void {}
        auto Range(ObjectType const&) const && -> void {}

        auto Range(ObjectType const& obj) & -> auto {
            return MakeSlice<false, false>(obj);
        }

        auto Range(ObjectType const& obj) const & -> auto {
            return MakeSlice<true, false>(obj);
        }
    };
}

#endif //OBJECT_ARRAY_ORDEREDRANGEDVIEWFACTORY_H
