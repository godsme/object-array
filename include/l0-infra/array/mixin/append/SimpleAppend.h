//
// Created by Darwin Yuan on 2021/7/9.
//

#ifndef OBJECT_ARRAY_2_SIMPLEAPPEND_H
#define OBJECT_ARRAY_2_SIMPLEAPPEND_H

namespace mixin {
    template<typename T>
    class SimpleAppend : public T {
        using Self = T;

    public:
        using typename Self::ObjectType;
        using typename Self::Maybe;

        using Self::Num;

    public:
        template<typename ... ARGS>
        auto Append(ARGS&& ... args) -> ObjectType* {
            if(Num() == Self::MAX_SIZE) return nullptr;
            return Self::Emplace(Num()++, std::forward<ARGS>(args)...);
        }

        template<typename ... ARGS>
        auto Append_I(ARGS&& ... args) -> Maybe {
            return Append(std::forward<ARGS>(args)...) == nullptr ? std::nullopt : Maybe(Num() - 1);
        }
    };
}

#endif //OBJECT_ARRAY_2_SIMPLEAPPEND_H
