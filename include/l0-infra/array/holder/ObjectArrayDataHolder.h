//
// Created by Darwin Yuan on 2021/6/21.
//

#ifndef OBJECT_ARRAY_OBJECTARRAYDATAHOLDER_H
#define OBJECT_ARRAY_OBJECTARRAYDATAHOLDER_H

#include <l0-infra/array/holder/detail/ContinuousArrayDataHolderInterface.h>
#include <l0-infra/array/holder/detail/ArrayHolderTrait.h>
#include <l0-infra/array/holder/ArrayDataHolder.h>
#include <l0-infra/base/DeduceSizeType.h>

namespace holder::detail {
    template<typename OBJ, std::size_t MAX_NUM>
    struct ObjectArrayHolder : private ArrayDataHolder<OBJ, MAX_NUM> {
        using Parent = ArrayDataHolder<OBJ, MAX_NUM>;
        using ObjectType = typename Parent::ObjectType;
        using SizeType = typename Parent::SizeType;
        using ElemType = typename Parent::ElemType;
        using Trait = typename Parent::Trait;
        using Owner = ObjectArrayHolder;
        constexpr static SizeType MAX_SIZE = MAX_NUM;
        constexpr static bool ORDERED = false;
        using Interface = ContinuousArrayDataHolderInterface<ObjectArrayHolder>;

        protected:
            using Parent::elems;

    private:
        template<typename>
        friend
        class ContinuousArrayDataHolderInterface;

        template<typename>
        friend
        class ArrayDataHolderInterface;

    private:
        template<typename U, std::enable_if_t<std::is_same_v<std::remove_const_t<U>, OBJ> ||
                                              std::is_same_v<std::remove_const_t<U>, ElemType>, int> = 0>
        auto ConstructFrom(U *array) -> void {
            if constexpr (std::is_trivially_copyable_v<ElemType>) {
                ::memcpy(elems, array, sizeof(ElemType) * num);
            } else {
                for (auto i = 0; i < num; i++) {
                    Trait::Emplace(elems[i], std::move(Trait::ToObject(array[i])));
                }
            }
        }

    protected:
        auto ClearContent() -> void {
            if constexpr (!std::is_trivially_destructible_v<ElemType>) {
                for (int i = 0; i < num; i++) Trait::Destroy(elems[i]);
            }
        }

        auto DoClear() -> void {
            ClearContent();
            num = 0;
        }

        auto MoveFrom(ObjectArrayHolder &&rhs) {
            ConstructFrom(rhs.elems);
            rhs.DoClear();
        }

        auto CopyFrom(OBJ const *array, std::size_t n) -> void {
            if constexpr(!std::is_trivially_destructible_v<ElemType>) {
                DoClear();
            }
            num = std::min(n, MAX_NUM);
            ConstructFrom(array);
        }

    public:
        ObjectArrayHolder() {}

        ObjectArrayHolder(std::initializer_list<OBJ> l) : num(std::min(l.size(), MAX_NUM)) {
            SizeType i = 0;
            for (auto &&elem : l) {
                if (i == num) break;
                Trait::Emplace(elems[i++], std::move(elem));
            }
        }

        ObjectArrayHolder(ObjectArrayHolder const &rhs) : num{rhs.num} {
            ConstructFrom(rhs.elems);
        }

        ObjectArrayHolder(ObjectArrayHolder &&rhs) : num{rhs.num} {
            MoveFrom(std::move(rhs));
        }

        auto operator=(ObjectArrayHolder const &rhs) -> ObjectArrayHolder & {
            DoClear();
            num = rhs.num;
            ConstructFrom(rhs.elems);
            return *this;
        }

        auto operator=(ObjectArrayHolder &&rhs) -> ObjectArrayHolder & {
            DoClear();
            num = rhs.num;
            MoveFrom(std::move(rhs));
            return *this;
        }

    protected:
        SizeType num{};
    };
}

namespace holder {
    template<typename OBJ, std::size_t MAX_NUM>
    using ObjectArrayDataHolder = detail::Holder<OBJ, MAX_NUM, detail::ObjectArrayHolder>;
}

#endif //OBJECT_ARRAY_OBJECTARRAYDATAHOLDER_H
