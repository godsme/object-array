//
// Created by Darwin Yuan on 2021/7/13.
//

#ifndef OBJECT_ARRAY_2_230DF641112B4D19B565E78ADBD06346
#define OBJECT_ARRAY_2_230DF641112B4D19B565E78ADBD06346


namespace mixin {
    template<typename T>
    struct ObjectCompareExt : T {
        using typename T::ObjectType;
        auto GetEqPred(ObjectType const& obj) const -> auto {
            if constexpr(std::is_rvalue_reference_v<decltype(T::GetEq())>) {
                return [&obj, &eq = T::GetEq()](ObjectType const& elem) { return eq(obj, elem); };
            } else {
                return [&obj, eq = T::GetEq()](ObjectType const& elem) { return eq(obj, elem); };
            }
        }

        auto GetGreater() -> auto {
            return [&less = T::GetLess()](ObjectType const& l, ObjectType const& r) {
                return less(r, l);
            };
        }
    };
}


#endif //OBJECT_ARRAY_2_230DF641112B4D19B565E78ADBD06346
