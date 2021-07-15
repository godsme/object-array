//
// Created by Darwin Yuan on 2021/7/12.
//

#ifndef OBJECT_ARRAY_2_83E7F8A480BD41019137E02FC593319F
#define OBJECT_ARRAY_2_83E7F8A480BD41019137E02FC593319F

namespace mixin {
    template<typename T>
    class ScopedArrayLikeEquality : public T {
        using Self = T;

    public:
        using T::GetNum;
        using T::Exists;

    public:
        auto operator==(ScopedArrayLikeEquality const &rhs) const -> bool {
            if (GetNum() != rhs.GetNum()) return false;
            return T::ForEach([&rhs](auto&& elem) {
                return rhs.Exists(elem);
            });
        }

        auto operator!=(ScopedArrayLikeEquality const &rhs) const -> bool {
            return !operator==(rhs);
        }
    };
}

#endif //OBJECT_ARRAY_2_83E7F8A480BD41019137E02FC593319F
