//
// Created by Darwin Yuan on 2021/7/13.
//

#ifndef OBJECT_ARRAY_2_34092CFC21414C5A84BD400DBA016887
#define OBJECT_ARRAY_2_34092CFC21414C5A84BD400DBA016887

namespace mixin {
    template<typename T>
    struct SimpleReplace : T {
        using typename T::ObjectType;
        using typename T::SizeType;
        using typename T::Maybe;

    public:
        template<typename ... ARGS>
        auto Replace(SizeType n, ARGS &&... args) -> ObjectType * {
            return (n < T::IndexEnd()) ? T::Unsafe_Replace(n, std::forward<ARGS>(args)...) : nullptr;
        }

        template<typename ... ARGS>
        auto Replace_I(SizeType n, ARGS &&... args) -> Maybe {
            return Replace(n, std::forward<ARGS>(args)...) == nullptr ? std::nullopt : Maybe(n);
        }
    };
}

#endif //OBJECT_ARRAY_2_34092CFC21414C5A84BD400DBA016887
