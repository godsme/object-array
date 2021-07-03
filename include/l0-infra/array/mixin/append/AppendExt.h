//
// Created by Darwin Yuan on 2021/6/29.
//

#ifndef OBJECT_ARRAY_APPENDEXT_H
#define OBJECT_ARRAY_APPENDEXT_H

#include <l0-infra/array/concept/Pred.h>

namespace mixin {
    template<typename T>
    class AppendExt : public T {
        using Self = T;

    public:
        using typename Self::ObjectType;

    public:
        using Self::Append;

        template<__sImPlE_pReD_cOnCePt(PRED), typename ... ARGS>
        auto FindOrAppend(PRED &&pred, ARGS&& ... args) -> ObjectType * {
            auto *found = Self::Find(std::forward<PRED>(pred));
            return found != nullptr ? found : Self::Append(std::forward<ARGS>(args)...);
        }

        auto FindOrAppend(ObjectType const& obj) -> ObjectType * {
            return FindOrAppend([&](auto&& elem) { return obj == elem; }, obj);
        }
    };
}

#endif //OBJECT_ARRAY_APPENDEXT_H
