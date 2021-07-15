//
// Created by Darwin Yuan on 2021/7/13.
//

#ifndef OBJECT_ARRAY_2_54FD3526DF75484BA4826C2971C0D630
#define OBJECT_ARRAY_2_54FD3526DF75484BA4826C2971C0D630

#include <l0-infra/base/detail/DeduceIntOptional.h>
#include <l0-infra/array/mixin/append/ProxyAppend.h>
#include <l0-infra/array/mixin/erase/ProxyErase.h>
#include <l0-infra/array/mixin/erase/DynamicRangedClear.h>
#include <l0-infra/array/mixin/array_like/PointerArrayLike.h>
#include <utility>

namespace holder::detail {
    template<typename ALLOCATOR, typename POINTER_ARRAY>
    struct DynamicArrayHolder {
        using ObjectType = typename ALLOCATOR::ObjectType;
        using PointerArray = POINTER_ARRAY;
        using SizeType = typename PointerArray::SizeType;
        constexpr static SizeType MAX_SIZE = PointerArray::MAX_SIZE;
        using Maybe = ::detail::DeduceIntOpt_t<MAX_SIZE>;
        constexpr static bool IS_CONST = false;
        constexpr static bool IS_ORDERED = false;

    private:
        auto ClearContent() {
            for (auto *pointer : pointers) {
                allocator.Remove(pointer);
            }
        }

    protected:
        auto DoClear() {
            ClearContent();
            pointers.Clear();
        }

    private:
        template<typename ... ARGS>
        auto Alloc(ARGS&& ... args) -> ObjectType * {
            if (pointers.All()) return nullptr;
            return allocator.Append(std::forward<ARGS>(args)...);
        }

    private:
        auto DoErase(SizeType n) -> void {
            if (n < pointers.GetNum()) {
                auto *p = pointers[n];
                allocator.Remove(p);
                pointers.Erase(n);
            }
        }

        auto CopyFrom(DynamicArrayHolder const &rhs) {
            if (!allocator.HasEnoughSlots(rhs.pointers.GetNum())) { return; }
            for (auto *pointer : rhs.pointers) {
                auto *p = allocator.Append(*pointer);
                if (p == nullptr) {
                    DoClear();
                    return;
                }
                pointers.Append(p);
            }
        }

        template<typename ... ARGS>
        auto DoAppend(ARGS &&... args) -> ObjectType * {
            auto *p = Alloc(std::forward<ARGS>(args)...);
            if (p == nullptr) return nullptr;
            pointers.Append(p);
            return p;
        }

        template<typename ... ARGS>
        auto DoAppend_I(ARGS &&... args) -> Maybe {
            auto *p = Alloc(std::forward<ARGS>(args)...);
            if (p == nullptr) return std::nullopt;
            return pointers.Append_I(p);
        }

        template<typename ... ARGS>
        auto DoReplace(SizeType n, ARGS &&... args) -> ObjectType * {
            if (n >= pointers.GetNum()) return nullptr;
            return allocator.ReplaceObj(pointers[n], std::forward<ARGS>(args)...);
        }

    public:
        template<typename ... ARGS>
        DynamicArrayHolder(ALLOCATOR &allocator, ARGS &&...args)
                : allocator{allocator}, pointers{std::forward<ARGS>(args)...} {}

        DynamicArrayHolder(DynamicArrayHolder const &rhs) : allocator{rhs.allocator} {
            CopyFrom(rhs);
        }

        DynamicArrayHolder(DynamicArrayHolder &&rhs)
                : allocator{rhs.allocator}, pointers(std::move(rhs.pointers)) {
        }

        auto operator=(DynamicArrayHolder const &rhs) -> DynamicArrayHolder & {
            DoClear();
            if (&allocator == &rhs.allocator) {
                CopyFrom(rhs);
            }
            return *this;
        }

        auto operator=(DynamicArrayHolder &&rhs) -> DynamicArrayHolder & {
            DoClear();
            if (&allocator == &rhs.allocator) {
                pointers = std::move(rhs.pointers);
            }
            return *this;
        }

    private:
        template<typename>
        friend class mixin::ProxyAppend;

        template<typename>
        friend class mixin::ProxyErase;

        template<typename>
        friend class mixin::PointerArrayLike;

        template<typename>
        friend class mixin::DynamicRangedClear;

    protected:
        ALLOCATOR &allocator;
        PointerArray pointers;
    };
}

namespace holder {
    template<typename ALLOCATOR, typename POINTER_ARRAY, bool FREE_ON_DTOR>
    struct DynamicArrayHolder : detail::DynamicArrayHolder<ALLOCATOR, POINTER_ARRAY> {
        using Parent = detail::DynamicArrayHolder<ALLOCATOR, POINTER_ARRAY>;
        using Parent::Parent;

        DynamicArrayHolder(DynamicArrayHolder const&) = default;
        DynamicArrayHolder(DynamicArrayHolder&&) = default;
        auto operator=(DynamicArrayHolder const&) -> DynamicArrayHolder& = default;
        auto operator=(DynamicArrayHolder&&) -> DynamicArrayHolder& = default;

        ~DynamicArrayHolder() {
            Parent::DoClear();
        }
    };

    template<typename ALLOCATOR, typename POINTER_ARRAY>
    struct DynamicArrayHolder<ALLOCATOR, POINTER_ARRAY, false>
            : detail::DynamicArrayHolder<ALLOCATOR, POINTER_ARRAY> {
        using Parent = detail::DynamicArrayHolder<ALLOCATOR, POINTER_ARRAY>;
        using Parent::Parent;
    };
}

#endif //OBJECT_ARRAY_2_54FD3526DF75484BA4826C2971C0D630
