//
// Created by Darwin Yuan on 2021/7/12.
//

#ifndef OBJECT_ARRAY_2_C6B5EEF1B6D7458EA77D28F115968AF7
#define OBJECT_ARRAY_2_C6B5EEF1B6D7458EA77D28F115968AF7

namespace mixin {
    template<typename T>
    struct OrderedReplace : T {
        using typename T::SizeType;
        using typename T::ObjectType;
        using typename T::Maybe;

    protected:
        using T::Elems;

    private:
        template<typename LESS>
        auto LeftMove(LESS&& less, SizeType i) -> auto* {
            do {
                std::swap(T::GetObject(i), T::GetObject(i-1));
            } while(--i > 0 && less(T::GetObject(i), T::GetObject(i-1)));

            return &T::GetObject(i);
        }

        template<typename LESS>
        auto RightMove(LESS&& less, SizeType i) -> auto* {
            auto boundary = T::Num() - 1;
            do {
                std::swap(T::GetObject(i), T::GetObject(i+1));
            } while(++i < boundary && less(T::GetObject(i+1), T::GetObject(i)));

            return &T::GetObject(i);
        }

        template<typename LESS, typename ... ARGS>
        auto DoReplace(LESS&& less, SizeType i, ARGS&& ... args) -> ObjectType* {
            auto* p = T::Unsafe_Replace(i, std::forward<ARGS>(args)...);
            if(i > 0 && less(T::GetObject(i), T::GetObject(i-1))) {
                return LeftMove(std::forward<LESS>(less), i);
            } else if(i < (T::Num() - 1) && less(T::GetObject(i+1), T::GetObject(i))) {
                return RightMove(std::forward<LESS>(less), i);
            } else {
                return p;
            }
        }

        template<typename LESS>
        auto DoReplaceIf(SizeType n, LESS&& less, ObjectType&& obj) -> ObjectType * {
            return less(obj, T::GetObject(n)) ? DoReplace(std::forward<LESS>(less), n, std::move(obj)) : nullptr;
        }

        template<typename LESS>
        auto DoReplaceIf(SizeType n, LESS&& less, ObjectType const& obj) -> ObjectType * {
            return less(obj, T::GetObject(n)) ? DoReplace(std::forward<LESS>(less), n, obj) : nullptr;
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

    protected:
        template<typename ... ARGS>
        auto ReplaceLastIf(ARGS&& ... args) -> ObjectType * {
            return DoReplaceIf(T::Num() - 1, T::GetLess(), std::forward<ARGS>(args)...);
        }

    public:
        template<typename ... ARGS>
        auto Replace(SizeType i, ARGS&& ... args) -> ObjectType* {
            return i < T::Num() ? DoReplace(T::GetLess(), i, std::forward<ARGS>(args)...) : nullptr;
        }

        template<typename ... ARGS>
        auto Replace_I(SizeType i, ARGS&& ... args) -> Maybe {
            auto* p = Replace(i, std::forward<ARGS>(args)...);
            return p == nullptr ? std::nullopt : Maybe{T::ObjectToIndex(p)};
        }
    };
}

#endif //OBJECT_ARRAY_2_C6B5EEF1B6D7458EA77D28F115968AF7
