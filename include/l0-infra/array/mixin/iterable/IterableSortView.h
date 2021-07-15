//
// Created by Darwin Yuan on 2021/7/12.
//

#ifndef OBJECT_ARRAY_2_43EFBD8908D74158A4A6531DE3231D9D
#define OBJECT_ARRAY_2_43EFBD8908D74158A4A6531DE3231D9D

#include <l0-infra/array/iterator/IndexBasedIterator.h>

namespace mixin {
    template<typename T>
    struct IterableSortView : T {
        using typename T::SizeType;
        using typename T::ObjectType;

    protected:
        using typename T::ThisType;

    private:
        using ConstIterator = iterator::PointerBasedIndexIterator<ThisType, std::add_const_t<ObjectType>, SizeType>;
        using Iterator = iterator::PointerBasedIndexIterator<ThisType, ObjectType, SizeType>;

    public:
        auto begin() const -> ConstIterator {
            return {T::ToThisType(), &T::GetIndices()[0]};
        }

        auto end() const -> ConstIterator {
            return {T::ToThisType(), &T::GetIndices()[T::GetIndices().GetNum()]};
        }

        auto begin() -> Iterator {
            return {T::ToThisType(), &T::GetIndices()[0]};
        }

        auto end() -> Iterator {
            return {T::ToThisType(), &T::GetIndices()[T::GetIndices().GetNum()]};
        }
    };
}

#endif //OBJECT_ARRAY_2_43EFBD8908D74158A4A6531DE3231D9D
