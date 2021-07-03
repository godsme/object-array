//
// Created by Darwin Yuan on 2021/7/3.
//

#ifndef OBJECT_ARRAY_ORDEREDREPLACE_H
#define OBJECT_ARRAY_ORDEREDREPLACE_H

#include <l0-infra/array/detail/ConceptDef.h>
#include <l0-infra/array/mixin/replace/OrderedDoReplace.h>

namespace mixin {
    template<typename T>
    class OrderedReplace : public OrderedDoReplace<T> {
        using Self = OrderedDoReplace<T>;

    public:
        using typename T::SizeType;
        using typename T::ObjectType;

    protected:
        using Self::Elems;
        using Self::GetLess;

    public:
        template<typename ... ARGS>
        auto DoReplace(SizeType i, ARGS&& ... args) -> ObjectType* {
            return Self::ActualReplace(GetLess(), i, std::forward<ARGS>(args)...);
        }
    };
}

#endif //OBJECT_ARRAY_ORDEREDREPLACE_H
