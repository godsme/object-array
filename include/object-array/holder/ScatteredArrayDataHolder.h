//
// Created by Darwin Yuan on 2021/6/21.
//

#ifndef OBJECT_ARRAY_SCATTEREDARRAYDATAHOLDER_H
#define OBJECT_ARRAY_SCATTEREDARRAYDATAHOLDER_H

#include <object-array/holder/ArrayDataHolder.h>
#include <object-array/holder/detail/ArrayDataHolderInterface.h>

namespace holder::detail {
    template<typename DATA_HOLDER>
    class ScatteredArrayDataHolderInterface : public ArrayDataHolderInterface<DATA_HOLDER>{
        dEcL_tHiS(DATA_HOLDER);
    public:
        using SizeType = typename DATA_HOLDER::SizeType;
        using BitMap = typename DATA_HOLDER::BitMap;
        using Trait = typename DATA_HOLDER::Trait;

        auto GetRange() const -> SizeType { return DATA_HOLDER::MAX_SIZE; }
        auto GetScope() const -> BitMap { return This()->GetOccupied(); }
    };
}

namespace holder {
    template<typename OBJ, std::size_t MAX_NUM>
    struct ScatteredArrayDataHolder : ArrayDataHolder<OBJ, MAX_NUM> {
        using Parent = ArrayDataHolder<OBJ, MAX_NUM>;
        using ObjectType = typename Parent::ObjectType;
        using ElemType = typename Parent::ElemType;
        using SizeType = typename Parent::SizeType;
        using BitMap = ::detail::ArrayScope<MAX_NUM>;
        using Trait = typename Parent::Trait;

        using Interface = detail::ScatteredArrayDataHolderInterface<ScatteredArrayDataHolder>;

    private:
        template<typename>
        friend class detail::ArrayDataHolderInterface;

    private:
        using Parent::elems;

        template<typename OP>
        auto ForAll(OP&& op) -> void {
            auto bits = occupied;
            for(auto i=0; bits.any(); i++, bits >>= 1) if(bits[0]) op(i);
        }

        auto Move(ScatteredArrayDataHolder&& rhs) {
            ForAll([&, this](auto i) {
                Trait::Emplace(elems[i], std::move(Trait::ToObject(rhs.elems[i])));
            });
            rhs.Clear();
        }

        auto Copy(ScatteredArrayDataHolder const& rhs) -> void {
            ForAll([&, this](auto i) {
                Trait::Emplace(elems[i], Trait::ToObject(rhs.elems[i]));
            });
        }

        template<typename ... ARGS>
        auto DoEmplace(SizeType i, ARGS&& ... args) -> auto* {
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
        auto CopyFrom(ScatteredArrayDataHolder const& rhs) -> void {
            if constexpr(!std::is_trivially_destructible_v<ElemType>) {
                ClearContent();
            }
            occupied = rhs.occupied;
            Copy(rhs);
        }

        auto MoveFrom(ScatteredArrayDataHolder&& rhs) -> void {
            if constexpr(!std::is_trivially_destructible_v<ElemType>) {
                ClearContent();
            }
            occupied = rhs.occupied;
            Move(std::move(rhs));
        }

    public:
        ScatteredArrayDataHolder() = default;
        ScatteredArrayDataHolder(std::initializer_list<OBJ> l) {
            SizeType i = 0;
            auto num = std::min(l.size(), MAX_NUM);
            for(auto&& obj : l) {
                if(i == num) break;
                occupied.set(i);
                Trait::Emplace(elems[i++], std::move(obj));
            }
        }

        ScatteredArrayDataHolder(ScatteredArrayDataHolder const& rhs) : occupied{rhs.occupied} {
            Copy(rhs);
        }

        ScatteredArrayDataHolder(ScatteredArrayDataHolder&& rhs) : occupied{rhs.occupied} {
            MoveFrom(std::move(rhs));
        }

        auto operator=(ScatteredArrayDataHolder const& rhs) -> ScatteredArrayDataHolder& {
            CopyFrom(rhs);
            return *this;
        }

        auto operator=(ScatteredArrayDataHolder&& rhs) -> ScatteredArrayDataHolder& {
            MoveFrom(std::move(rhs));
            return *this;
        }

        auto Clear() -> void {
            ClearContent();
            occupied.reset();
        }

        auto RangeSize() const -> SizeType {
            return Parent::MAX_SIZE;
        }

        auto GetOccupied() const -> BitMap {
            return occupied;
        }

        template<typename ... ARGS>
        auto Append(ARGS &&... args) -> ObjectType * {
            if (!occupied.all()) {
                for(auto i=0; i<MAX_NUM; i++) {
                    if(occupied[i]) continue;
                    return DoEmplace(i, std::forward<ARGS>(args)...);
                }
            }
            return nullptr;
        }

    private:
        BitMap occupied;
    };
}

#endif //OBJECT_ARRAY_SCATTEREDARRAYDATAHOLDER_H
