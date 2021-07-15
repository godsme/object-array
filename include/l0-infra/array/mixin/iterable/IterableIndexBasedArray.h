//
// Created by Darwin Yuan on 2021/7/12.
//

#ifndef OBJECT_ARRAY_2_D8A03C0EDDF049359E9810874658B1B4
#define OBJECT_ARRAY_2_D8A03C0EDDF049359E9810874658B1B4

#include <l0-infra/array/iterator/IndexBasedIterator.h>

namespace mixin {
    template<typename T>
    struct IterableIndexBasedArray : T {
        using typename T::SizeType;
        using typename T::ObjectType;

    protected:
        using typename T::ThisType;

    private:
        using ConstIterator = iterator::IndicesBasedIndexIterator<ThisType const, std::add_const_t<ObjectType>, SizeType>;
        using Iterator = iterator::IndicesBasedIndexIterator<ThisType, ObjectType, SizeType>;

    public:
        auto begin() const -> ConstIterator {
            return {T::ToThisType(), T::IndexBegin()};
        }

        auto end() const -> ConstIterator {
            return {T::ToThisType(), T::IndexEnd()};
        }

        auto begin() -> Iterator {
            return {T::ToThisType(), T::IndexBegin()};
        }

        auto end() -> Iterator {
            return {T::ToThisType(), T::IndexEnd()};
        }
    };
}

#endif //OBJECT_ARRAY_2_D8A03C0EDDF049359E9810874658B1B4
