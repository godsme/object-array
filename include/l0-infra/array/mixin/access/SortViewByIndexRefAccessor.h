//
// Created by Darwin Yuan on 2021/7/12.
//

#ifndef OBJECT_ARRAY_2_112F2F1FF7704E36B3FA5768319140CB
#define OBJECT_ARRAY_2_112F2F1FF7704E36B3FA5768319140CB

namespace mixin {
    template<typename T>
    struct SortViewByIndexRefAccessor : T {
        using typename T::SizeType;
        using typename T::ObjectType;

        auto operator[](SizeType n) const -> ObjectType const& {
            return T::GetObject(T::GetIndices()[n]);
        }

        auto operator[](SizeType n) -> ObjectType& {
            return T::GetObject(T::GetIndices()[n]);
        }
    };
}

#endif //OBJECT_ARRAY_2_112F2F1FF7704E36B3FA5768319140CB
