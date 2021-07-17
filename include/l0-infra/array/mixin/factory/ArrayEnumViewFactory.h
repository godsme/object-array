//
// Created by Darwin Yuan on 2021/7/17.
//

#ifndef OBJECT_ARRAY_B5F09D7F651B4FFBB0FD81CEFB3BDBE9
#define OBJECT_ARRAY_B5F09D7F651B4FFBB0FD81CEFB3BDBE9

namespace mixin {
    template<typename T>
    struct ArrayEnumViewFactory : T {
        auto Enumerate() & -> auto {
            return T::WithIndex();
        }

        auto Enumerate() const & -> auto {
            return T::WithIndex();
        }

        auto Enumerate() && = delete;
        auto Enumerate() const && = delete;
    };
}


#endif //OBJECT_ARRAY_B5F09D7F651B4FFBB0FD81CEFB3BDBE9
