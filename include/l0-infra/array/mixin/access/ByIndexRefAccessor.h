//
// Created by Darwin Yuan on 2021/7/9.
//

#ifndef OBJECT_ARRAY_2_BYINDEXREFACCESSOR_26AA05F3EB9F44C08CAC08D2D20B8B28
#define OBJECT_ARRAY_2_BYINDEXREFACCESSOR_26AA05F3EB9F44C08CAC08D2D20B8B28

namespace mixin {
    template<typename T>
    class ByIndexRefAccessor : public T {
        using Self = T;

    public:
        using typename T::SizeType;
        using typename T::ObjectType;

        auto operator[](SizeType n) const -> ObjectType const& {
            return Self::GetObject(n + Self::IndexBegin());
        }

        auto operator[](SizeType n) -> ObjectType& {
            return Self::GetObject(n + Self::IndexBegin());
        }
    };
}

#endif //OBJECT_ARRAY_2_BYINDEXREFACCESSOR_26AA05F3EB9F44C08CAC08D2D20B8B28
