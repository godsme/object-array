//
// Created by Darwin Yuan on 2021/7/13.
//

#ifndef OBJECT_ARRAY_2_EAF51F8ABDA640DA966DD84CE718836C
#define OBJECT_ARRAY_2_EAF51F8ABDA640DA966DD84CE718836C

namespace mixin {
    template<typename T>
    struct ViewReplace : T {
        using T::IndexBegin;
        using T::IndexEnd;

    protected:
        using T::GetArray;

    public:
        using typename T::SizeType;
        using typename T::ObjectType;
        using typename T::Maybe;

    public:
        template<typename ... ARGS>
        auto Replace(SizeType i, ARGS &&... args) -> ObjectType * {
            auto index = i + IndexBegin();
            return i >= IndexEnd() ? nullptr : GetArray().Replace(index, std::forward<ARGS>(args)...);
        }

        template<typename ... ARGS>
        auto Replace_I(SizeType i, ARGS &&... args) -> Maybe {
            auto index = i + IndexBegin();
            return i >= IndexEnd() ? std::nullopt : GetArray().Replace_I(index, std::forward<ARGS>(args)...);
        }
    };
}

#endif //OBJECT_ARRAY_2_EAF51F8ABDA640DA966DD84CE718836C
