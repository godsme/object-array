//
// Created by Darwin Yuan on 2021/6/24.
//

#ifndef OBJECT_ARRAY_SIMPLEMUTATEEXT_H
#define OBJECT_ARRAY_SIMPLEMUTATEEXT_H

namespace mixin {
    template<typename T>
    class SimpleMutateExt : public T {
        using Self = T;
    public:
        using typename T::ObjectType;
        using typename T::SizeType;
        using typename T::BitMap;

    public:
        using Self::GetObj;

        using Self::IndexBegin;
        using Self::IndexEnd;

        using Self::Append;
        using Self::Replace;
        using Self::Erase;
        using Self::Find;
        using Self::FindIndex;

        template<typename ... ARGS>
        auto ReplaceObj(ObjectType const& obj, ARGS &&... args) -> ObjectType * {
            auto* base = &GetObj(0);
            if(&obj < base) return nullptr;
            return Replace(&obj - base, std::forward<ARGS>(args)...);
        }

        auto Remove(ObjectType *p) -> void {
            auto* base = &GetObj(0);
            if (p < base) return;
            Erase(p - base);
        }

        auto CleanUp(BitMap scope) -> void {
            if(IndexEnd() == 0) return;
            for(auto i=IndexEnd()-1; i>=IndexBegin(); --i) {
                if(scope[i]) Erase(i);
            }
        }

        auto CleanUpEx(BitMap excluded) -> void {
            CleanUp(~excluded);
        }

        template<typename PRED>
        auto FindOrAppend(PRED&& pred) -> ObjectType * {
            auto* found = Find(std::forward<PRED>(pred));
            return found ? found : Append();
        }

        template<typename PRED>
        auto RemoveBy(PRED&& pred) -> void {
            auto found = FindIndex(std::forward<PRED>(pred));
            if(found) Erase(*found);
        }
    };
}

#endif //OBJECT_ARRAY_SIMPLEMUTATEEXT_H
