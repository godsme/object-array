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
    class ScatteredArrayDataHolderInterface : public ArrayDataHolderInterface1<DATA_HOLDER>{
        dEcL_tHiS(typename DATA_HOLDER::Inner);
    public:
        using SizeType = typename DATA_HOLDER::SizeType;
        using BitMap = typename DATA_HOLDER::BitMap;
        using Trait = typename DATA_HOLDER::Trait;
        using ObjectType = typename DATA_HOLDER::ObjectType;
        using Owner = typename DATA_HOLDER::Owner;

        auto GetRange() const -> SizeType { return DATA_HOLDER::MAX_SIZE; }
        auto GetScope() const -> BitMap { return This()->GetOccupied(); }

        template<typename ... ARGS>
        auto Append(ARGS &&... args) -> ObjectType * {
            return This()->Append(std::forward<ARGS>(args)...);
        }

        template<typename ... ARGS>
        auto Replace(SizeType n, ARGS &&... args) -> ObjectType * {
            return This()->Replace(n, std::forward<ARGS>(args)...);
        }

        auto Erase(SizeType n) -> void {
            This()->Erase(n);
        }
    };
}

namespace holder::detail {
    template<typename OBJ, std::size_t MAX_NUM, typename MIXINS>
    struct ScatteredArrayDataHolder {
        using Parent = ArrayDataHolder<OBJ, MAX_NUM>;
        using ObjectType = typename Parent::ObjectType;
        using ElemType = typename Parent::ElemType;
        using SizeType = typename Parent::SizeType;
        using BitMap = ::detail::ArrayScope<MAX_NUM>;
        using Trait = typename Parent::Trait;
        using Owner = ScatteredArrayDataHolder;
        constexpr static SizeType MAX_SIZE = MAX_NUM;

        struct Inner : ArrayDataHolder<OBJ, MAX_NUM>
                , MIXINS::template type<detail::ScatteredArrayDataHolderInterface<ScatteredArrayDataHolder<OBJ, MAX_NUM, MIXINS>>> {

        private:
            template<typename>
            friend class detail::ArrayDataHolderInterface1;

        private:
            using Parent::elems;

            using Parent::ElemToObject;
            using Parent::ConstElemToObject;

            template<typename OP>
            auto ForAll(OP &&op) -> void {
                auto bits = occupied;
                for (auto i = 0; bits.any(); i++, bits >>= 1) if (bits[0]) op(i);
            }

            auto Move(Inner &&rhs) {
                ForAll([&, this](auto i) {
                    Trait::Emplace(elems[i], std::move(Trait::ToObject(rhs.elems[i])));
                });
                rhs.Clear();
            }

            auto Copy(Inner const &rhs) -> void {
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

            auto MoveFrom(Inner &&rhs) -> void {
                if constexpr(!std::is_trivially_destructible_v<ElemType>) {
                    ClearContent();
                }
                occupied = rhs.occupied;
                Move(std::move(rhs));
            }

        public:
            Inner() {};

            Inner(std::initializer_list<OBJ> l) {
                SizeType i = 0;
                auto num = std::min(l.size(), MAX_NUM);
                for (auto &&obj : l) {
                    if (i == num) break;
                    occupied.set(i);
                    Trait::Emplace(elems[i++], std::move(obj));
                }
            }

            Inner(Inner const &rhs) : occupied{rhs.occupied} {
                Copy(rhs);
            }

            Inner(Inner &&rhs) : occupied{rhs.occupied} {
                MoveFrom(std::move(rhs));
            }

            auto operator=(Inner const &rhs) -> Inner & {
                CopyFrom(rhs);
                return *this;
            }

            auto operator=(Inner &&rhs) -> Inner & {
                MoveFrom(std::move(rhs));
                return *this;
            }

            auto Clear() -> void {
                ClearContent();
                occupied.reset();
            }

            auto GetOccupied() const -> BitMap {
                return occupied;
            }

            template<typename ... ARGS>
            auto Append(ARGS &&... args) -> ObjectType * {
                if (!occupied.all()) {
                    for (auto i = 0; i < MAX_NUM; i++) {
                        if (occupied[i]) continue;
                        return DoEmplace(i, std::forward<ARGS>(args)...);
                    }
                }
                return nullptr;
            }

            template<typename ... ARGS>
            auto Replace(SizeType i, ARGS &&... args) -> ObjectType * {
                if (i >= MAX_NUM) return nullptr;
                if (occupied[i]) {
                    return Trait::Replace(elems[i], std::forward<ARGS>(args)...);
                } else {
                    return DoEmplace(i, std::forward<ARGS>(args)...);
                }
            }

            auto Erase(SizeType i) -> void {
                if (occupied[i]) {
                    Trait::Destroy(elems[i]);
                    occupied.reset(i);
                }
            }

        private:
            BitMap occupied;
        };
    };
}

namespace holder {
    template<typename OBJ, std::size_t MAX_NUM, typename MIXINS>
    using ScatteredArrayHolder = typename detail::Holder<OBJ, MAX_NUM, MIXINS, detail::ScatteredArrayDataHolder>;
}


#endif //OBJECT_ARRAY_SCATTEREDARRAYDATAHOLDER_H
