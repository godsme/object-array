//
// Created by Darwin Yuan on 2021/7/9.
//

#ifndef OBJECT_ARRAY_2_INDEXEDAPPEND_ADA81A67BA304CAA908A1AAE951B6305
#define OBJECT_ARRAY_2_INDEXEDAPPEND_ADA81A67BA304CAA908A1AAE951B6305

namespace mixin {
    template<typename T>
    struct IndicesAppend : T {
        using Self = T;

    public:
        using typename Self::ObjectType;
        using typename Self::Maybe;

    protected:
        using Self::This;

    public:
        template<typename ... ARGS>
        auto Append_I(ARGS&& ... args) -> Maybe {
            auto index = Self::GetArray().Append_I(std::forward<ARGS>(args)...);
            if(index) Self::GetIndices().Append(*index);
            return index;
        }

        template<typename ... ARGS>
        auto Append(ARGS&& ... args) -> ObjectType* {
            auto index = Append_I(std::forward<ARGS>(args)...);
            return index ? &Self::GetArray()[*index] : nullptr;
        }
    };
}

#endif //OBJECT_ARRAY_2_INDEXEDAPPEND_ADA81A67BA304CAA908A1AAE951B6305
