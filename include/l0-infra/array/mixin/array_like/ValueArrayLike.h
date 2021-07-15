//
// Created by Darwin Yuan on 2021/7/13.
//

#ifndef OBJECT_ARRAY_2_25B6BBFC016B4CA7A0235C6EB53AC20F
#define OBJECT_ARRAY_2_25B6BBFC016B4CA7A0235C6EB53AC20F

namespace mixin {
    template<typename T>
    struct ValueArrayLike : T {
    protected:
        using T::This;
        using typename T::DataHolder;

    public:
        using typename T::ElemType;
        using typename T::ObjectType;
        using typename T::SizeType;

        template<typename ... ARGS>
        auto Emplace(SizeType n, ARGS&& ... args) -> ObjectType* {
            if constexpr(std::is_aggregate_v<ElemType>) {
                T::Elems()[n] = ElemType{std::forward<ARGS>(args)...};
            } else {
                T::Elems()[n] = ElemType(std::forward<ARGS>(args)...);
            }
            return T::Elems() + n;
        }

        auto Destroy(SizeType n) -> void {
            if constexpr(!std::is_trivially_destructible_v<ElemType>) {
                T::Elems()[n].~ElemType();
            }
        }

        template<typename ... ARGS>
        auto Unsafe_Replace(SizeType n, ARGS&& ... args) -> ObjectType* {
            Destroy(n);
            return Emplace(n, std::forward<ARGS>(args)...);
        }

        auto MoveObject(SizeType to, SizeType from) -> ObjectType* {
            return Emplace(to, std::move(T::Elems()[from]));
        }
    };
}

#endif //OBJECT_ARRAY_2_25B6BBFC016B4CA7A0235C6EB53AC20F
