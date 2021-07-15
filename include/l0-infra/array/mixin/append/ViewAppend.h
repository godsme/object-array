//
// Created by Darwin Yuan on 2021/7/9.
//

#ifndef OBJECT_ARRAY_2_VIEWAPPEND_1F68099983914E038E8F6B8AC2B5C2DD
#define OBJECT_ARRAY_2_VIEWAPPEND_1F68099983914E038E8F6B8AC2B5C2DD

namespace mixin {
    template<typename T>
    class ViewAppend : public T {
        using Self = T;

    public:
        template<typename ... ARGS>
        auto Append(ARGS&& ... args) -> auto* {
            return Self::GetArray().Append(std::forward<ARGS>(args)...);
        }

        template<typename ... ARGS>
        auto Append_I(ARGS&& ... args) -> auto {
            return Self::GetArray().Append_I(std::forward<ARGS>(args)...);
        }
    };
}

#endif //OBJECT_ARRAY_2_VIEWAPPEND_1F68099983914E038E8F6B8AC2B5C2DD
