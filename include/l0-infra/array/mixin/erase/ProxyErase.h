//
// Created by Darwin Yuan on 2021/7/13.
//

#ifndef OBJECT_ARRAY_2_85ECC60AA6354B7D9AB7EB848370C249
#define OBJECT_ARRAY_2_85ECC60AA6354B7D9AB7EB848370C249

namespace mixin {
    template<typename T>
    struct ProxyErase : T {
        using typename T::SizeType;

    protected:
        using T::This;

    public:
        auto Erase(SizeType i) -> void {
            This()->DoErase(i);
        }
    };
}

#endif //OBJECT_ARRAY_2_85ECC60AA6354B7D9AB7EB848370C249
