//
// Created by Darwin Yuan on 2021/7/9.
//

#ifndef OBJECT_ARRAY_2_INDEXEDORDEREDARRAYHOLDER_DD3D729ECD2B4524883B485F74369546
#define OBJECT_ARRAY_2_INDEXEDORDEREDARRAYHOLDER_DD3D729ECD2B4524883B485F74369546

#include <l0-infra/array/OrderedObjectArray.h>
#include <l0-infra/array/mixin/array_like/IndexedArrayLike.h>
#include <l0-infra/array/mixin/array_like/ViewedArray.h>
#include <l0-infra/array/mixin/less/OrderedArrayLike.h>

namespace holder {
    template<typename ARRAY, typename LESS>
    struct IndexedOrderedArrayHolder {
        using ObjectType = typename ARRAY::ObjectType;
        using SizeType = typename ARRAY::SizeType;
        using ArrayType = std::decay_t<ARRAY>;
        constexpr static SizeType MAX_SIZE = ARRAY::MAX_SIZE;
        constexpr static bool IS_CONST = false;
        constexpr static bool IS_ORDERED = true;

        IndexedOrderedArrayHolder() {}
        IndexedOrderedArrayHolder(LESS const& less) : indices{less} {}

    private:
        template<typename>
        friend class mixin::IndexedArrayLike;

        template<typename>
        friend class mixin::ViewedArray;

        template<typename>
        friend class mixin::OrderedArrayLike;

    private:
        struct Less : LESS {
            Less() {}
            Less(LESS const& less) : LESS(less) {}

            auto operator()(SizeType l, SizeType r) const -> bool {
                return LESS::operator()(array[l], array[r]);
            }
            ARRAY array;
        };

        using IndicesBase = OrderedObjectArray<SizeType, MAX_SIZE, Less>;
        struct Indices : IndicesBase {
            using Parent = IndicesBase;
            using Parent::Parent;
            Indices() {}

            auto GetArray() -> ARRAY& {
                return Parent::GetLess().array;
            }

            auto GetArray() const -> ARRAY const& {
                return Parent::GetLess().array;
            }

            auto GetObjectLess() -> LESS& {
                return Parent::GetLess();
            }

            auto GetObjectLess() const -> LESS const& {
                return Parent::GetLess();
            }
        };

    private:
        auto GetArray() const -> ARRAY const& {
            return indices.GetArray();
        }

        auto GetArray() -> ARRAY& {
            return indices.GetArray();
        }

        auto GetIndices() const -> Indices const& {
            return indices;
        }

        auto GetIndices() -> Indices& {
            return indices;
        }

        auto GetObjectLess() const -> LESS const& {
            return indices.GetObjectLess();
        }

        auto GetObjectLess() -> LESS& {
            return indices.GetObjectLess();
        }

    private:
        Indices indices;
    };
}

#endif //OBJECT_ARRAY_2_INDEXEDORDEREDARRAYHOLDER_DD3D729ECD2B4524883B485F74369546
