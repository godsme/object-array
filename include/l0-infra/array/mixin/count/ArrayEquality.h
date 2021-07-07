//
// Created by Darwin Yuan on 2021/6/28.
//

#ifndef OBJECT_ARRAY_ARRAYEQUALITY_H
#define OBJECT_ARRAY_ARRAYEQUALITY_H

namespace mixin {
    template<typename T>
    class ArrayEquality : public T {
        using Self = T;

    public:
        using T::GetNum;
        using T::operator[];
        using T::Exists;

    public:
        auto operator==(ArrayEquality const &rhs) const -> bool {
            if (GetNum() != rhs.GetNum()) return false;

            for (auto i = 0; i < GetNum(); i++) {
                if constexpr(T::IS_ORDERED) {
                    if ((*this)[i] != rhs[i]) return false;
                } else {
                    if (!rhs.Exists((*this)[i])) return false;
                }
            }
            return true;
        }

        auto operator!=(ArrayEquality const &rhs) const -> bool {
            return !operator==(rhs);
        }
    };
}

#endif //OBJECT_ARRAY_ARRAYEQUALITY_H
