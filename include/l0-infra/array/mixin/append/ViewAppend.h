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
        template<typename ... ARGS>
        auto DoAppend(ARGS&& ... args) -> typename Self::ObjectType* {
            return Self::GetArray().DoAppend(std::forward<ARGS>(args)...);
        }
    };
}

#endif //OBJECT_ARRAY_VIEWAPPEND_H
