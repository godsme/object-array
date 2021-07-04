//
// Created by Darwin Yuan on 2021/7/4.
//

#ifndef OBJECT_ARRAY_INDEXBASEDITERATOR_H
#define OBJECT_ARRAY_INDEXBASEDITERATOR_H

namespace iterator {
    template<typename ARRAY, typename OBJ_TYPE>
    struct IndexBasedIterator {
        using SizeType = typename ARRAY::SizeType;

        IndexBasedIterator(ARRAY& array, SizeType index) : array{array}, index{index} {}

        auto operator++() -> IndexBasedIterator& {
            ++index;
            return *this;
        }

        auto operator!=(IndexBasedIterator const& rhs) const -> bool {
            return index != rhs.index;
        }

        auto operator*() -> OBJ_TYPE& {
            return array.GetObj(index);
        }

    private:
        SizeType index;
        ARRAY& array;
    };
}

#endif //OBJECT_ARRAY_INDEXBASEDITERATOR_H
