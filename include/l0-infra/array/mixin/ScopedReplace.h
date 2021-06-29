//
// Created by Darwin Yuan on 2021/6/29.
//

#ifndef OBJECT_ARRAY_SCOPEDREPLACE_H
#define OBJECT_ARRAY_SCOPEDREPLACE_H

namespace mixin {
    template<typename T>
    class ScopedReplace : public T {
        using Self = T;
    public:
        using typename T::SizeType;
        using typename T::ObjectType;

    protected:
        using Self::GetArray;
        using Self::IndexBegin;
        using Self::IndexEnd;
        using Self::GetScope;

    public:
        template<typename ... ARGS>
        auto Replace(SizeType i, ARGS &&... args) -> ObjectType * {
            auto index = i + IndexBegin();
            return i >= IndexEnd() || !GetScope()[index] ? nullptr : GetArray().Replace(index, std::forward<ARGS>(args)...);
        }
    };
}

#endif //OBJECT_ARRAY_SCOPEDREPLACE_H
