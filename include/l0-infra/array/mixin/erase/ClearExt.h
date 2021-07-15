//
// Created by Darwin Yuan on 2021/7/10.
//

#ifndef OBJECT_ARRAY_2_7AF06BB5C51444CEB000124E2CF760BD
#define OBJECT_ARRAY_2_7AF06BB5C51444CEB000124E2CF760BD

namespace mixin {
    template<typename T>
    class ClearExt : public T {
        using Self = T;

    public:
        using typename T::OffsetType;
        using typename T::SizeType;

    private:
        auto OffsetToIndex(OffsetType offset) const -> SizeType {
            return offset.ToIndex(Self::Num());
        }

    public:
        using Self::Clear;

        auto ClearFrom(OffsetType from) -> void {
            T::DoClearFrom(OffsetToIndex(from));
        }

        auto Clear(OffsetType from, OffsetType until) -> void {
            T::Unsafe_Clear(OffsetToIndex(from), OffsetToIndex(until));
        }

        auto ClearUntil(OffsetType until) -> void {
            T::Unsafe_Clear(0, OffsetToIndex(until));
        }
    };
}

#endif //OBJECT_ARRAY_2_7AF06BB5C51444CEB000124E2CF760BD
