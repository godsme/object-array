//
// Created by Darwin Yuan on 2021/6/21.
//

#ifndef OBJECT_ARRAY_SCATTEREDARRAYDATAHOLDER_H
#define OBJECT_ARRAY_SCATTEREDARRAYDATAHOLDER_H

#include <l0-infra/array/holder/ArrayDataHolder.h>
#include <l0-infra/array/holder/detail/ArrayDataHolderInterface.h>
#include <l0-infra/array/holder/detail/ArrayHolderTrait.h>

namespace holder::detail {
    template<typename DATA_HOLDER>
    class ScatteredArrayDataHolderInterface : public ArrayDataHolderInterface<DATA_HOLDER> {
        dEcL_tHiS(DATA_HOLDER);
    public:
        using SizeType = typename DATA_HOLDER::SizeType;
        using BitMap = typename DATA_HOLDER::BitMap;
        using Trait = typename DATA_HOLDER::Trait;
        using ObjectType = typename DATA_HOLDER::ObjectType;
        constexpr static SizeType MAX_SIZE = DATA_HOLDER::MAX_SIZE;

        auto GetRange() const -> SizeType { return MAX_SIZE; }
        auto GetScope() const -> BitMap { return This()->occupied; }

        template<typename ... ARGS>
        auto Append(ARGS &&... args) -> ObjectType * {
            if (!This()->occupied.all()) {
                for (auto i = 0; i < MAX_SIZE; i++) {
                    if (This()->occupied[i]) continue;
                    return This()->DoEmplace(i, std::forward<ARGS>(args)...);
                }
            }
            return nullptr;
        }

        template<typename ... ARGS>
        auto Replace(SizeType i, ARGS &&... args) -> ObjectType * {
            if (i >= MAX_SIZE) return nullptr;
            if (This()->occupied[i]) {
                return Trait::Replace(This()->elems[i], std::forward<ARGS>(args)...);
            } else {
                return This()->DoEmplace(i, std::forward<ARGS>(args)...);
            }
        }

        auto Erase(SizeType i) -> void {
            if (This()->occupied[i]) {
                Trait::Destroy(This()->elems[i]);
                This()->occupied.reset(i);
            }
        }
    };
}

namespace holder::detail {
    template<typename OBJ, std::size_t MAX_NUM>
    struct ScatteredArrayDataHolder : private ArrayDataHolder<OBJ, MAX_NUM> {
        using Parent = ArrayDataHolder<OBJ, MAX_NUM>;
        using ObjectType = typename Parent::ObjectType;
        using ElemType = typename Parent::ElemType;
        using SizeType = typename Parent::SizeType;
        using BitMap = ::detail::ArrayScope<MAX_NUM>;
        using Trait = typename Parent::Trait;
        using Owner = ScatteredArrayDataHolder;
        constexpr static SizeType MAX_SIZE = MAX_NUM;
        constexpr static bool IS_ORDERED = false;
        using Interface = detail::ScatteredArrayDataHolderInterface<ScatteredArrayDataHolder>;

    private:
        template<typename>
        friend class detail::ArrayDataHolderInterface;

        template<typename>
        friend class detail::ScatteredArrayDataHolderInterface;

    private:
        using Parent::elems;

        using Parent::ElemToObject;
        using Parent::ConstElemToObject;

        template<typename OP>
        auto ForAll(OP &&op) -> void {
            auto bits = occupied;
            for (auto i = 0; bits.any(); i++, bits >>= 1) if (bits[0]) op(i);
        }

        auto Move(ScatteredArrayDataHolder &&rhs) {
            ForAll([&, this](auto i) {
                Trait::Emplace(elems[i], std::move(Trait::ToObject(rhs.elems[i])));
            });
            rhs.Clear();
        }

        auto Copy(ScatteredArrayDataHolder const &rhs) -> void {
            ForAll([&, this](auto i) {
                Trait::Emplace(elems[i], Trait::ToObject(rhs.elems[i]));
            });
        }

        template<typename ... ARGS>
        auto DoEmplace(SizeType i, ARGS &&... args) -> auto * {
            occupied.set(i);
            return Trait::Emplace(elems[i], std::forward<ARGS>(args)...);
        }

    protected:
        auto ClearContent() -> void {
            if constexpr (!std::is_trivially_destructible_v<ElemType>) {
                ForAll([this](auto i) { Trait::Destroy(elems[i]); });
            }
        }

    protected:
        auto CopyFrom(ScatteredArrayDataHolder const &rhs) -> void {
            if constexpr(!std::is_trivially_destructible_v<ElemType>) {
                ClearContent();
            }
            occupied = rhs.occupied;
            Copy(rhs);
        }

        auto MoveFrom(ScatteredArrayDataHolder &&rhs) -> void {
            if constexpr(!std::is_trivially_destructible_v<ElemType>) {
                ClearContent();
            }
            occupied = rhs.occupied;
            Move(std::move(rhs));
        }

    public:
        ScatteredArrayDataHolder() {};

        ScatteredArrayDataHolder(std::initializer_list<OBJ> l) {
            SizeType i = 0;
            auto num = std::min(l.size(), MAX_NUM);
            for (auto &&obj : l) {
                if (i == num) break;
                occupied.set(i);
                Trait::Emplace(elems[i++], std::move(obj));
            }
        }

        ScatteredArrayDataHolder(ScatteredArrayDataHolder const &rhs) : occupied{rhs.occupied} {
            Copy(rhs);
        }

        ScatteredArrayDataHolder(ScatteredArrayDataHolder &&rhs) : occupied{rhs.occupied} {
            MoveFrom(std::move(rhs));
        }

        auto operator=(ScatteredArrayDataHolder const &rhs) -> ScatteredArrayDataHolder & {
            CopyFrom(rhs);
            return *this;
        }

        auto operator=(ScatteredArrayDataHolder &&rhs) -> ScatteredArrayDataHolder & {
            MoveFrom(std::move(rhs));
            return *this;
        }

        auto Clear() -> void {
            ClearContent();
            occupied.reset();
        }

//        auto GetOccupied() const -> BitMap {
//            return occupied;
//        }

    private:
        BitMap occupied;
    };
}

namespace holder {
    template<typename OBJ, std::size_t MAX_NUM>
    using ScatteredArrayHolder = detail::Holder<OBJ, MAX_NUM, detail::ScatteredArrayDataHolder>;
}

#endif //OBJECT_ARRAY_SCATTEREDARRAYDATAHOLDER_H
