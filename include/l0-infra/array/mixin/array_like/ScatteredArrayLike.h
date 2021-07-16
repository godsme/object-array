//
// Created by Darwin Yuan on 2021/7/9.
//

#ifndef OBJECT_ARRAY_2_SCATTEREDARRAYLIKE_H
#define OBJECT_ARRAY_2_SCATTEREDARRAYLIKE_H

namespace mixin {
    template<typename T>
    struct ScatteredArrayLike : T {
    protected:
        using T::This;

    public:
        using typename T::SizeType;
        using typename T::BitMap;
        using typename T::Maybe;
        using typename T::ObjectType;

        template<typename ... ARGS>
        auto Append(ARGS &&... args) -> ObjectType * {
            if (!This()->occupied.all()) {
                for (auto i = 0; i < T::MAX_SIZE; i++) {
                    if (This()->occupied[i]) continue;
                    return This()->DoEmplace(i, std::forward<ARGS>(args)...);
                }
            }
            return nullptr;
        }

        template<typename ... ARGS>
        auto Append_I(ARGS &&... args) -> Maybe {
            if (!This()->occupied.all()) {
                for (auto i = 0; i < T::MAX_SIZE; i++) {
                    if (This()->occupied[i]) continue;
                    This()->DoEmplace(i, std::forward<ARGS>(args)...);
                    return i;
                }
            }
            return std::nullopt;
        }

        template<typename ... ARGS>
        auto Replace(SizeType i, ARGS &&... args) -> ObjectType * {
            if (This()->occupied[i]) {
                return T::Unsafe_Replace(i, std::forward<ARGS>(args)...);
            } else {
                return i < T::MAX_SIZE ? This()->DoEmplace(i, std::forward<ARGS>(args)...) : nullptr;
            }
        }

        template<typename ... ARGS>
        auto Replace_I(SizeType i, ARGS &&... args) -> Maybe {
            return Replace(i, std::forward<ARGS>(args)...) == nullptr ? std::nullopt : Maybe{i};
        }

        auto Erase(SizeType i) -> void {
            if (This()->occupied[i]) {
                T::Destroy(i);
                This()->occupied.reset(i);
            }
        }

        auto Clear() -> void {
            This()->DoClear();
        }
    };
}

#endif //OBJECT_ARRAY_2_SCATTEREDARRAYLIKE_H
