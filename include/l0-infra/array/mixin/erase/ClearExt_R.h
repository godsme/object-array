//
// Created by Darwin Yuan on 2021/7/17.
//

#ifndef OBJECT_ARRAY_724AB587EB464F22AB75062CFE4D0929
#define OBJECT_ARRAY_724AB587EB464F22AB75062CFE4D0929


namespace mixin {
    template<typename T>
    struct ClearExt_R : T {
        using typename T::OffsetType;

    protected:
        using typename T::ThisType;

    public:
        using T::Clear;
        using T::ClearFrom;
        using T::ClearUntil;

        auto Clear() && -> ThisType {
            return T::Clear();
        }

        auto Clear(OffsetType from, OffsetType until) && -> ThisType {
            return T::Clear(from, until);
        }

        auto ClearFrom(OffsetType from) && -> ThisType {
            return T::ClearFrom(from);
        }

        auto ClearUntil(OffsetType until) && -> ThisType {
            return T::ClearUntil(until);
        }
    };
}

#endif //OBJECT_ARRAY_724AB587EB464F22AB75062CFE4D0929
