//
// Created by Darwin Yuan on 2021/7/10.
//

#ifndef OBJECT_ARRAY_2_7AF06BB5C51444CEB000124E2CF760BD
#define OBJECT_ARRAY_2_7AF06BB5C51444CEB000124E2CF760BD

namespace mixin {
    template<typename T>
    struct ClearExt : T {
        using typename T::OffsetType;
        using typename T::SizeType;

    protected:
        using typename T::ThisType;

    private:
        auto OffsetToIndex(OffsetType offset) const -> SizeType {
            return offset.ToIndex(T::IndexEnd());
        }

    public:
        auto Clear() & -> ThisType& {
            T::Clear();
            return T::ToThisType();
        }

        auto Clear() && = delete;

        auto Clear(OffsetType from, OffsetType until) & -> ThisType& {
            T::Unsafe_Clear(OffsetToIndex(from), OffsetToIndex(until));
            return T::ToThisType();
        }

        auto Clear(OffsetType from, OffsetType until) && = delete;

        auto ClearFrom(OffsetType from) & -> ThisType& {
            T::DoClearFrom(OffsetToIndex(from));
            return T::ToThisType();
        }

        auto ClearFrom(OffsetType from) && = delete;

        auto ClearUntil(OffsetType until) & -> ThisType& {
            T::Unsafe_Clear(0, OffsetToIndex(until));
            return T::ToThisType();
        }

        auto ClearUntil(OffsetType until) && = delete;
    };
}

#endif //OBJECT_ARRAY_2_7AF06BB5C51444CEB000124E2CF760BD
