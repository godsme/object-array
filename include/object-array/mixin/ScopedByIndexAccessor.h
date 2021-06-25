//
// Created by Darwin Yuan on 2021/6/24.
//

#ifndef OBJECT_ARRAY_SCOPEDBYINDEXACCESSOR_H
#define OBJECT_ARRAY_SCOPEDBYINDEXACCESSOR_H

#include <object-array/concept/RangedArrayLike.h>
#include <object-array/mixin/detail/Mixins.h>
#include <l0-infra/base/InvokeConstMethod.h>

namespace mixin {
    template<__cOnCePt(SimpleScopedRangedArrayLike) T>
    class ScopedByIndexAccessor : public T {
        using Self = T;

    public:
        using typename T::SizeType;
        using typename T::ObjectType;

        using Self::IndexBegin;
        using Self::IndexEnd;
        using Self::GetObj;
        using Self::GetScope;

        auto At(SizeType n) const -> ObjectType const* {
            auto index = n + IndexBegin();
            return !(GetScope().test(index) && index < IndexEnd()) ? nullptr : &GetObj(index);
        }

        auto At(SizeType n) -> ObjectType * {
            return __INVOKE_CONST_METHOD(At(n));
        }

        auto First() const -> auto* {
            auto&& scope = GetScope();
            for(auto i = IndexBegin(); i < IndexEnd(); ++i) {
                if(scope[i]) return &GetObj(i);
            }
            return nullptr;
        }

        auto First() -> auto* {
            return __INVOKE_CONST_METHOD(Last());
        }

        auto Last() const -> ObjectType const* {
            if(IndexEnd() == IndexBegin()) return nullptr;
            auto&& scope = GetScope();
            for(int i = IndexEnd()-1; i >= IndexBegin(); --i) {
                if(scope[i]) return &GetObj(i);
            }
            return nullptr;
        }

        auto Last() -> auto* {
            return __INVOKE_CONST_METHOD(Last());
        }
    };
}

#endif //OBJECT_ARRAY_SCOPEDBYINDEXACCESSOR_H
