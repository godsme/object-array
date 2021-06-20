//
// Created by Darwin Yuan on 2021/6/20.
//

#ifndef OBJECT_ARRAY_MIXINDEF_H
#define OBJECT_ARRAY_MIXINDEF_H

namespace mixin {
    template<typename T>
    struct Mixin {
        auto Self() const -> T const * {
            return reinterpret_cast<T const *>(this);
        }

        auto Self() -> T * {
            return reinterpret_cast<T *>(this);
        }
    };

#define __DEF_Array_MIXIN(mixin) \
class mixin : protected Mixin<T>

}
#endif //OBJECT_ARRAY_MIXINDEF_H
