//
// Created by Darwin Yuan on 2021/7/14.
//

#ifndef OBJECT_ARRAY_2_9FEF18F0F66D41F79008C7F0DBF1B4FB
#define OBJECT_ARRAY_2_9FEF18F0F66D41F79008C7F0DBF1B4FB

namespace mixin {
    template<typename T>
    struct ClearExporter : T {
        using T::Clear;
    };
}

#endif //OBJECT_ARRAY_2_9FEF18F0F66D41F79008C7F0DBF1B4FB
