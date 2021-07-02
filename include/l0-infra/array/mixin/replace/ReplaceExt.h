//
// Created by Darwin Yuan on 2021/6/29.
//

#ifndef OBJECT_ARRAY_REPLACEEXT_H
#define OBJECT_ARRAY_REPLACEEXT_H

#include <l0-infra/array/detail/ConceptDef.h>
#include <l0-infra/array/concept/SimpleMutable.h>
#include <l0-infra/array/concept/Pred.h>

namespace mixin {
    template<typename T>
    class ReplaceExt : public T {
        using Self = T;

    public:
        using typename Self::ObjectType;
        using typename Self::SizeType;

    public:
        using Self::Replace;

        template<__sImPlE_pReD_cOnCePt(PRED), typename ... ARGS>
        auto ReplaceBy(PRED&& pred, ARGS&& ... args) -> ObjectType * {
            auto index = Self::FindIndex(std::forward<PRED>(pred));
            return index ? Self::Replace(*index, std::forward<ARGS>(args)...) : nullptr;
        }

        template<typename ... ARGS>
        auto ReplaceObj(ObjectType const& obj, ARGS &&... args) -> ObjectType * {
            return ReplaceBy([&](auto&& elem) { return obj == elem; }, std::forward<ARGS>(args)...);
        }

        template<typename ... ARGS>
        auto ReplaceObj(ObjectType const* p, ARGS &&... args) -> ObjectType * {
            auto index = GetObjIndex(p);
            return index ? Self::Replace(*index, std::forward<ARGS>(args)...) : nullptr;
        }
    };
}

#endif //OBJECT_ARRAY_REPLACEEXT_H
