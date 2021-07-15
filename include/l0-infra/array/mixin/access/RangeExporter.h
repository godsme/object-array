//
// Created by Darwin Yuan on 2021/7/10.
//

#ifndef OBJECT_ARRAY_2_6AD33680649B46B8A971C31F5100F101
#define OBJECT_ARRAY_2_6AD33680649B46B8A971C31F5100F101

namespace mixin {
    template<typename T>
    struct RangeExporter : T {
        using T::IndexBegin;
        using T::IndexEnd;
        using T::GetObject;
    };
}

#endif //OBJECT_ARRAY_2_6AD33680649B46B8A971C31F5100F101
