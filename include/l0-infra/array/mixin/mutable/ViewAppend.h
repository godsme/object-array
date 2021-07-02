//
// Created by Darwin Yuan on 2021/6/29.
//

#ifndef OBJECT_ARRAY_VIEWAPPEND_H
#define OBJECT_ARRAY_VIEWAPPEND_H

namespace mixin {
    template<typename T>
    class ViewAppend : public T {
        using Self = T;

    public:
        using typename Self::ObjectType;

    public:
        template<typename ... ARGS>
        auto Append(ARGS&& ... args) -> ObjectType* {
            return Self::GetArray().Append(std::forward<ARGS>(args)...);
        }
    };
}

#endif //OBJECT_ARRAY_VIEWAPPEND_H
