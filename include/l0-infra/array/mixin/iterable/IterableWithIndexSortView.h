//
// Created by Darwin Yuan on 2021/7/12.
//

#ifndef OBJECT_ARRAY_2_3F8FAC5E62554B3BA5D760C6A0B55D62
#define OBJECT_ARRAY_2_3F8FAC5E62554B3BA5D760C6A0B55D62

#include <l0-infra/array/iterator/SortViewWithIndexIterator.h>

namespace mixin {
    template<typename T>
    struct IterableWithIndexSortView : T {
        using Self = T;
    public:
        using typename T::SizeType;
        using typename T::ObjectType;

    private:
        auto GetIndicesObject(SizeType n) const -> SizeType* {
            return const_cast<SizeType*>(&T::GetArray().GetIndices()[n]);
        }

        auto GetViewedArray() const -> decltype(auto) {
            return T::GetArray().GetArray();
        }

        auto GetViewedArray() -> decltype(auto) {
            return T::GetArray().GetArray();
        }
    public:
        auto begin() const -> auto {
            return iterator::SortViewWithIndexIterator{GetViewedArray(), GetIndicesObject(T::IndexBegin())};
        }

        auto end() const -> auto {
            return iterator::SortViewWithIndexIterator{GetViewedArray(), GetIndicesObject(T::IndexEnd())};
        }

        auto begin() -> auto {
            return iterator::SortViewWithIndexIterator{GetViewedArray(), GetIndicesObject(T::IndexBegin())};
        }

        auto end() -> auto {
            return iterator::SortViewWithIndexIterator{GetViewedArray(), GetIndicesObject(T::IndexEnd())};
        }
    };
}

#endif //OBJECT_ARRAY_2_3F8FAC5E62554B3BA5D760C6A0B55D62
