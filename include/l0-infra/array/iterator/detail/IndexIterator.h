//
// Created by Darwin Yuan on 2021/7/12.
//

#ifndef OBJECT_ARRAY_2_8FDEB907672442E5ADA0EAE13E8C5184
#define OBJECT_ARRAY_2_8FDEB907672442E5ADA0EAE13E8C5184

namespace iterator {
    template<typename ARRAY, typename OBJ_TYPE>
    class EnumIterator;
}

namespace iterator::detail {

    template<typename SizeType>
    struct IndexIterator {
        IndexIterator(SizeType index) : index{index} {}

        auto operator!=(IndexIterator const& rhs) const -> bool {
            return index != rhs.index;
        }

    protected:
        auto StepForward() -> void { ++index; }
        auto SkipForward() -> void { ++index; };
        auto GetValue() const -> SizeType { return index; }

        template<typename ARRAY, typename OBJ_TYPE>
        friend class ::iterator::EnumIterator;

    protected:
        SizeType index;
    };
}

#endif //OBJECT_ARRAY_2_8FDEB907672442E5ADA0EAE13E8C5184
