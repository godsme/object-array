//
// Created by Darwin Yuan on 2021/7/14.
//

#ifndef OBJECT_ARRAY_2_0BFB8077B100489AA942CE66C9D8CC76
#define OBJECT_ARRAY_2_0BFB8077B100489AA942CE66C9D8CC76

#include <l0-infra/array/ObjectArray.h>
#include <l0-infra/array/ScatteredArray.h>
#include <l0-infra/array/holder/detail/Holder.h>
#include <l0-infra/array/mixin/array_like/IndexedArrayLike.h>
#include <l0-infra/array/mixin/array_like/ViewedArray.h>
#include <l0-infra/array/mixin/less/OrderedArrayLike.h>

namespace holder::detail {
    template<typename OBJ, std::size_t MAX_NUM>
    struct IndexedArrayHolder {
        static_assert(!std::is_reference_v<OBJ>);

        using ObjectType = OBJ;
        using ArrayType = ScatteredArray<std::decay_t<OBJ>, MAX_NUM>;
        using SizeType = typename ArrayType::SizeType;
        constexpr static SizeType MAX_SIZE = MAX_NUM;
        constexpr static bool IS_CONST = std::is_const_v<OBJ>;
        constexpr static bool IS_ORDERED = false;

        IndexedArrayHolder() {}

        IndexedArrayHolder(std::initializer_list<OBJ> l) {
            auto n = 0;
            for (auto i = l.begin(); i < l.end(); ++i) {
                if (n++ == MAX_SIZE) break;
                indices.Append(*array.Append_I(*i));
            }
        }

    protected:
        auto ClearContent() -> void {}

    private:
        template<typename>
        friend
        class mixin::IndexedArrayLike;

        template<typename>
        friend
        class mixin::ViewedArray;

        template<typename>
        friend
        class mixin::OrderedArrayLike;

    private:
        auto GetArray() const -> ArrayType const & {
            return array;
        }

        auto GetArray() -> ArrayType & {
            return array;
        }

        auto GetIndices() const -> decltype(auto) {
            return (indices);
        }

        auto GetIndices() -> decltype(auto) {
            return (indices);
        }

        auto GetObjectLess() const -> decltype(auto) {
            return array.GetLess();
        }

        auto GetObjectLess() -> decltype(auto) {
            return array.GetLess();
        }

    private:
        ArrayType array;
        ObjectArray<SizeType, MAX_SIZE> indices;
    };

}

namespace holder::const_trait {
    template<typename OBJ, std::size_t MAX_NUM, bool = std::is_const_v<OBJ>>
    struct IndexedArrayHolder : detail::IndexedArrayHolder<OBJ, MAX_NUM> {
        using Parent = detail::IndexedArrayHolder<OBJ, MAX_NUM>;
        using Parent::Parent;

        using ConstArrayHolder = IndexedArrayHolder<std::add_const_t<OBJ>, MAX_NUM>;
        using NonConstArrayHolder = IndexedArrayHolder<std::remove_const_t<OBJ>, MAX_NUM>;

        IndexedArrayHolder() {}

        IndexedArrayHolder(ConstArrayHolder const& rhs) : Parent{rhs} {}
        IndexedArrayHolder(ConstArrayHolder&& rhs) : Parent{std::move(rhs)} {}
        IndexedArrayHolder(NonConstArrayHolder const& rhs) : Parent{rhs} {}
        IndexedArrayHolder(NonConstArrayHolder&& rhs) : Parent{std::move(rhs)} {}

        auto operator=(ConstArrayHolder const &) -> IndexedArrayHolder & = delete;
        auto operator=(ConstArrayHolder&&) -> IndexedArrayHolder & = delete;
        auto operator=(NonConstArrayHolder const &) -> IndexedArrayHolder & = delete;
        auto operator=(NonConstArrayHolder&&) -> IndexedArrayHolder & = delete;
    };

    template<typename OBJ, std::size_t MAX_NUM>
    struct IndexedArrayHolder<OBJ, MAX_NUM, false> : detail::IndexedArrayHolder<OBJ, MAX_NUM> {
        using Parent = detail::IndexedArrayHolder<OBJ, MAX_NUM>;
        using Parent::Parent;

        using ConstArrayHolder = IndexedArrayHolder<std::add_const_t<OBJ>, MAX_NUM>;
        using NonConstArrayHolder = IndexedArrayHolder<std::remove_const_t<OBJ>, MAX_NUM>;

        IndexedArrayHolder() {}

        IndexedArrayHolder(ConstArrayHolder const& rhs) : Parent{rhs} {}
        IndexedArrayHolder(ConstArrayHolder&& rhs) : Parent{std::move(rhs)} {}
        IndexedArrayHolder(NonConstArrayHolder const& rhs) : Parent{rhs} {}
        IndexedArrayHolder(NonConstArrayHolder&& rhs) : Parent{std::move(rhs)} {}

        auto operator=(ConstArrayHolder const &rhs) -> IndexedArrayHolder & {
            Parent::operator=(rhs);
            return *this;
        }

        auto operator=(ConstArrayHolder&& rhs) -> IndexedArrayHolder & {
            Parent::operator=(std::move(rhs));
            return *this;
        }

        auto operator=(NonConstArrayHolder const &rhs) -> IndexedArrayHolder & {
            Parent::operator=(rhs);
            return *this;
        }

        auto operator=(NonConstArrayHolder&& rhs) -> IndexedArrayHolder & {
            Parent::operator=(std::move(rhs));
            return *this;
        }
    };

    template<typename OBJ, std::size_t MAX_NUM>
    using IndexedArray = IndexedArrayHolder<OBJ, MAX_NUM>;
}

namespace holder {
    template<typename OBJ, std::size_t MAX_NUM>
    using IndexedArrayHolder = holder::detail::Holder<OBJ, MAX_NUM, const_trait::IndexedArray>;
}

#endif //OBJECT_ARRAY_2_0BFB8077B100489AA942CE66C9D8CC76
