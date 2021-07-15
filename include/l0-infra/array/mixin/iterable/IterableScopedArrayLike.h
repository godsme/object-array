//
// Created by Darwin Yuan on 2021/7/12.
//

#ifndef OBJECT_ARRAY_2_5DCB71950B9B4CFEB251CC5EED16FBE3
#define OBJECT_ARRAY_2_5DCB71950B9B4CFEB251CC5EED16FBE3

#include <l0-infra/array/iterator/ScopeIterator.h>

namespace mixin {
    template<typename T>
    struct IterableScopedArrayLike : T {
        using typename T::SizeType;
        using typename T::ObjectType;
        using typename T::BitMap;

        using T::IndexBegin;

        using T::GetScope;

    protected:
        using typename T::ThisType;

    private:
        using ConstIterator = iterator::ScopeIterator<ThisType const, std::add_const_t<ObjectType>, SizeType, BitMap>;
        using Iterator = iterator::ScopeIterator<ThisType, ObjectType, SizeType, BitMap>;

        using EndIterator = iterator::EmptyIterator;

    public:
        auto begin() const -> ConstIterator {
            return {GetScope() >> IndexBegin(), T::ToThisType(), IndexBegin()};
        }

        auto end() const -> EndIterator {
            return {};
        }

        auto begin() -> Iterator {
            return {GetScope() >> IndexBegin(), T::ToThisType(), IndexBegin()};
        }

        auto end() -> EndIterator {
            return {};
        }
    };
}

#endif //OBJECT_ARRAY_2_5DCB71950B9B4CFEB251CC5EED16FBE3
