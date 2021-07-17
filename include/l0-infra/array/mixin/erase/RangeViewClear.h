//
// Created by Darwin Yuan on 2021/7/17.
//

#ifndef OBJECT_ARRAY_F194E32B342F4070AE7B26A2F129E150
#define OBJECT_ARRAY_F194E32B342F4070AE7B26A2F129E150

namespace mixin {
    template<typename T>
    struct RangeViewClear : T {
        // r-value slice could do Clear, because we don't have to maintain
        // the integrity of Slice.
        auto Clear() && -> void {
            T::GetArray().Clear(T::IndexBegin(), T::IndexEnd());
        }

        auto Clear() & = delete;
    };
}

#endif //OBJECT_ARRAY_F194E32B342F4070AE7B26A2F129E150
