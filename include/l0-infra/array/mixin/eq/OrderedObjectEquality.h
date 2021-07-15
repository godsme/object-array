//
// Created by Darwin Yuan on 2021/7/13.
//

#ifndef OBJECT_ARRAY_2_CA4FE0925F9D45CEA3DC9293A37C03B2
#define OBJECT_ARRAY_2_CA4FE0925F9D45CEA3DC9293A37C03B2

#include <l0-infra/base/detail/BinaryOpDetect.h>

namespace mixin {
    template<typename T>
    struct OrderedObjectEquality : T {
        using typename T::ObjectType;

    public:
        auto GetEq() const -> decltype(auto) {
            if constexpr(::detail::equality::IS_EQ_COMPARABLE<ObjectType>) {
                return (::detail::equality::EQ_COMPARE<ObjectType>);
            } else {
                return [&less = T::GetLess()](ObjectType const& l, ObjectType const& r) -> bool {
                    return !(less(l, r) || less(r, l));
                };
            }
        }
    };
}

#endif //OBJECT_ARRAY_2_CA4FE0925F9D45CEA3DC9293A37C03B2
