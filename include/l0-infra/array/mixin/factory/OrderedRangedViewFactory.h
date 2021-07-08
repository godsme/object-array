//
// Created by Darwin Yuan on 2021/7/8.
//

#ifndef OBJECT_ARRAY_ORDEREDRANGEDVIEWFACTORY_H
#define OBJECT_ARRAY_ORDEREDRANGEDVIEWFACTORY_H

#include <l0-infra/array/concept/RangedArrayLike.h>
#include <l0-infra/array/mixin/factory/InternalRangedViewFactory.h>

namespace mixin {
    template<typename T>
    class OrderedRangedViewFactory : public InternalRangedViewFactory<T> {
        using Self = InternalRangedViewFactory<T>;

    public:
        using typename T::SizeType;
        using typename T::ObjectType;

    protected:
        using Self::IndexBegin;
        using Self::IndexEnd;
        using Self::GetLess;

    protected:
        template<bool AS_CONST, bool R_VALUE, typename PRED>
        auto MakeSlice(PRED&& pred) const -> auto {
            auto from = Self::FindIndex(std::forward<PRED>(pred));
            if(!from) {
                return Self::template DoMakeSlice<AS_CONST, R_VALUE, false>(IndexEnd(), IndexEnd());
            } else {
                SizeType until = *from;
                for(; until<IndexEnd(); until++) {
                    if(!pred(Self::GetObj(until))) break;
                }
                return Self::template DoMakeSlice<AS_CONST, R_VALUE, false>(*from, until);
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
