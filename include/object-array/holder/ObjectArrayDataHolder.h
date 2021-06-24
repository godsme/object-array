//
// Created by Darwin Yuan on 2021/6/21.
//

#ifndef OBJECT_ARRAY_OBJECTARRAYDATAHOLDER_H
#define OBJECT_ARRAY_OBJECTARRAYDATAHOLDER_H

#include <object-array/holder/detail/ContinuousArrayDataHolderInterface.h>
#include <object-array/holder/detail/ArrayHolderTrait.h>
#include <object-array/holder/ArrayDataHolder.h>
#include <cub/base/DeduceSizeType.h>

namespace holder::detail {
    template<typename OBJ, std::size_t MAX_NUM>
    struct ObjectArrayHolder : ArrayDataHolder<OBJ, MAX_NUM> {
        using Parent = ArrayDataHolder<OBJ, MAX_NUM>;
        using SizeType = typename Parent::SizeType;
        using ElemType = typename Parent::ElemType;
        using Trait = typename Parent::Trait;
        using Interface = ContinuousArrayDataHolderInterface<ObjectArrayHolder>;

    private:
        template<typename>
        friend class ContinuousArrayDataHolderInterface;

        template<typename>
        friend class ArrayDataHolderInterface;

        using Parent::elems;

        template<typename U, std::enable_if_t<std::is_same_v<std::remove_const_t<U>, OBJ> || std::is_same_v<std::remove_const_t<U>, ElemType>, int> = 0>
        auto ConstructFrom(U* array) -> void {
            if constexpr (std::is_trivially_copyable_v<ElemType>) {
                ::memcpy(elems, array, sizeof(ElemType) * num);
            } else {
                for(auto i=0; i<num; i++) {
                    Trait::Emplace(elems[i], std::move(Trait::ToObject(array[i])));
                }
            }
        }

        auto ClearContent(SizeType from, SizeType until) -> void {
            if constexpr (!std::is_trivially_destructible_v<ElemType>) {
                for(int i=from; i<until; i++) Trait::Destroy(elems[i]);
            }
        }

        auto CleanOrdered(SizeType from, SizeType until) {
            auto total = num - until;
            if constexpr (std::is_trivially_copyable_v<ElemType>) {
                ::memmove(elems + from, elems + until, sizeof(ElemType) * total);
            } else {
                for(auto i=0; i<total; i++) {
                    Trait::Emplace(elems[from+i], std::move(Trait::ToObject(elems[until + i])));
                }
            }
        }

        auto Clean(SizeType from, SizeType until) {
            auto total = std::min(until - from, num - until);
            if constexpr (std::is_trivially_copyable_v<ElemType>) {
                ::memmove(elems + from, elems + num - total, sizeof(ElemType) * total);
            } else {
                auto moveFrom = num - total;
                for(auto i=0; i<total; i++) {
                    Trait::Emplace(elems[from+i], std::move(Trait::ToObject(elems[moveFrom + i])));
                }
            }
        }

    public:
        auto ClearContent() -> void {
            ClearContent(0, num);
        }

        auto ClearFrom(SizeType from = 0) -> void {
            ClearContent(from, num);
            num = std::min(from, num);
        }

        auto Clear() -> void {
            ClearFrom(0);
        }

        template<bool ORDERED>
        auto ClearRange(SizeType from, SizeType until) -> void {
            if(from >= until || until >= num) return;
            ClearContent(from, until);
            if constexpr(ORDERED) {
                CleanOrdered(from, until);
            } else {
                Clean(from, until);
            }
            num -= (until - from);
        }

        auto MoveFrom(ObjectArrayHolder&& rhs) {
            ConstructFrom(rhs.elems);
            rhs.Clear();
        }

        auto CopyFrom(OBJ const* array, std::size_t n) -> void {
            if constexpr(!std::is_trivially_destructible_v<ElemType>) {
                Clear();
            }
            num = std::min(n, MAX_NUM);
            ConstructFrom(array);
        }

    public:
        ObjectArrayHolder() = default;
        ObjectArrayHolder(std::initializer_list<OBJ> l) : num(std::min(l.size(), MAX_NUM)) {
            SizeType i = 0;
            for(auto&& elem : l) {
                if(i == num) break;
                Trait::Emplace(elems[i++], std::move(elem));
            }
        }

        ObjectArrayHolder(ObjectArrayHolder const& rhs) : num{rhs.num} {
            ConstructFrom(rhs.elems);
        }

        ObjectArrayHolder(ObjectArrayHolder&& rhs) : num{rhs.num} {
            MoveFrom(std::move(rhs));
        }

        auto operator=(ObjectArrayHolder const& rhs) -> ObjectArrayHolder& {
            Clear();
            num = rhs.num;
            ConstructFrom(rhs.elems);
            return *this;
        }

        auto operator=(ObjectArrayHolder&& rhs) -> ObjectArrayHolder& {
            Clear();
            num = rhs.num;
            MoveFrom(std::move(rhs));
            return *this;
        }

    private:
        SizeType num{};
    };
}

namespace holder {
    template<typename OBJ, std::size_t MAX_NUM>
    using ObjectArrayDataHolder = typename detail::Holder<OBJ, MAX_NUM, detail::ObjectArrayHolder>;
}

#endif //OBJECT_ARRAY_OBJECTARRAYDATAHOLDER_H
