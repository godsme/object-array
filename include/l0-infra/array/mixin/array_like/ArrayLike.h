//
// Created by Darwin Yuan on 2021/7/8.
//

#ifndef OBJECT_ARRAY_2_ARRAYLIKE_H
#define OBJECT_ARRAY_2_ARRAYLIKE_H

namespace mixin {
    template<typename T>
    struct ArrayLike : T {
    protected:
        using T::This;
        using typename T::DataHolder;

    public:
        using typename T::ElemType;
        using typename T::ObjectType;
        using typename T::SizeType;


        template<typename ... ARGS>
        auto Emplace(SizeType n, ARGS&& ... args) -> ObjectType* {
            return T::Elems()[n].Emplace(std::forward<ARGS>(args)...);
        }

        template<typename ... ARGS>
        auto Unsafe_Replace(SizeType n, ARGS&& ... args) -> ObjectType* {
            return T::Elems()[n].Replace(std::forward<ARGS>(args)...);
        }

        auto Destroy(SizeType n) -> void {
            return T::Elems()[n].Destroy();
        }

        auto ReplaceObject(SizeType to, SizeType from) -> ObjectType* {
            return T::Elems()[to].Replace(std::move(DataHolder::ElemToObject(T::Elems()[from])));
        }
    };
}

#endif //OBJECT_ARRAY_2_ARRAYLIKE_H
