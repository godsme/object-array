//
// Created by Darwin Yuan on 2021/7/16.
//

#ifndef OBJECT_ARRAY_E17DAF15F4BA4918B3B6976FFC095E16
#define OBJECT_ARRAY_E17DAF15F4BA4918B3B6976FFC095E16


namespace mixin {
    template<typename T>
    struct OrderedReplaceLastIf : T {
        using typename T::SizeType;
        using typename T::ObjectType;
        using typename T::Maybe;

    private:
        template<typename LESS>
        auto DoReplaceIf(SizeType n, LESS&& less, ObjectType&& obj) -> ObjectType * {
            return less(obj, T::GetObject(n)) ? T::Replace(n, std::move(obj)) : nullptr;
        }

        template<typename LESS>
        auto DoReplaceIf(SizeType n, LESS&& less, ObjectType const& obj) -> ObjectType * {
            return less(obj, T::GetObject(n)) ? T::Replace(n, obj) : nullptr;
        }

        template<typename ... ARGS>
        auto ConstructObject(ARGS&& ... args) -> ObjectType {
            if constexpr(std::is_aggregate_v<ObjectType>) {
                return ObjectType{std::forward<ARGS>(args)...};
            } else {
                return ObjectType(std::forward<ARGS>(args)...);
            }
        }

        template<typename LESS, typename ... ARGS>
        auto DoReplaceIf(SizeType n, LESS&& less, ARGS &&... args) -> ObjectType * {
            return DoReplaceIf(n, std::forward<LESS>(less), ConstructObject(std::forward<ARGS>(args)...));
        }

    public:
        template<typename ... ARGS>
        auto ReplaceLastIf(ARGS&& ... args) -> ObjectType * {
            return DoReplaceIf(T::Num() - 1, T::GetLess(), std::forward<ARGS>(args)...);
        }

        template<typename ... ARGS>
        auto ReplaceLastIf_I(ARGS&& ... args) -> Maybe {
            return T::ObjectToIndex(ReplaceLastIf(std::forward<ARGS>(args)...));
        }
    };
}

#endif //OBJECT_ARRAY_E17DAF15F4BA4918B3B6976FFC095E16
