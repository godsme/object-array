//
// Created by Darwin Yuan on 2021/7/10.
//

#ifndef OBJECT_ARRAY_2_01BA3FD4CE2747E79C62F9F712BD608E
#define OBJECT_ARRAY_2_01BA3FD4CE2747E79C62F9F712BD608E

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

            auto&& eq = T::GetEq();
            for (auto i = 0; i < GetNum(); i++) {
                if constexpr(T::IS_ORDERED) {
                    if(!eq((*this)[i], rhs[i])) return false;
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

#endif //OBJECT_ARRAY_2_01BA3FD4CE2747E79C62F9F712BD608E
