//
// Created by Darwin Yuan on 2021/6/24.
//

#ifndef OBJECT_ARRAY_SIMPLEMUTATEEXT_H
#define OBJECT_ARRAY_SIMPLEMUTATEEXT_H

#include <l0-infra/array/concept/SimpleMutable.h>

namespace mixin {
    template<__cOnCePt(SimpleMutable) T>
    class SimpleMutateExt : public T {
        using Self = T;
    public:
        using typename Self::ObjectType;
        using typename Self::SizeType;
        using typename Self::BitMap;
        using typename Self::Maybe;

    protected:
        using Self::GetObj;
        using Self::IndexBegin;
        using Self::GetObjIndex;

    public:
        template<typename ... ARGS>
        auto ReplaceObj(ObjectType const& obj, ARGS &&... args) -> ObjectType * {
            auto index = GetObjIndex(&obj);
            return index ? Self::Replace(*index, std::forward<ARGS>(args)...) : nullptr;
        }

        auto Remove(ObjectType *p) -> void {
            auto index = GetObjIndex(p);
            if (index) Self::Erase(*index);
        }
    };
}

#endif //OBJECT_ARRAY_SIMPLEMUTATEEXT_H
