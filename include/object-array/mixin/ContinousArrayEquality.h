//
// Created by Darwin Yuan on 2021/6/24.
//

#ifndef OBJECT_ARRAY_CONTINOUSARRAYEQUALITY_H
#define OBJECT_ARRAY_CONTINOUSARRAYEQUALITY_H

namespace mixin {
    template<typename T>
    struct ContinuousArrayEquality : T {
        auto operator==(ContinuousArrayEquality const &rhs) const -> bool {
            if (GetNum() != rhs.GetNum()) return false;

            for (auto i = 0; i < GetNum(); i++) {
                if constexpr(ORDERED) {
                    if ((*this)[i] != rhs[i]) return false;
                } else {
                    if (!rhs.Exists((*this)[i])) return false;
                }
            }

            return true;
        }

        auto operator!=(ContinuousArrayEquality const &rhs) const -> bool {
            return !operator==(rhs);
        }
    }
}
#endif //OBJECT_ARRAY_CONTINOUSARRAYEQUALITY_H
