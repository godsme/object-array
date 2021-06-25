//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_FOO_H
#define OBJECT_ARRAY_FOO_H

#include <l0-infra/base/BitSet.h>
#include <l0-infra/base/IntOpt.h>
#include <cstddef>

namespace ut {
    template<typename T>
    struct FooInterface {
    protected:
        auto This() const -> T const* {
            return reinterpret_cast<T const*>(this);
        }

        auto This() -> T* {
            return reinterpret_cast<T*>(this);
        }

    public:
        using SizeType = typename T::SizeType;
        using ObjectType = typename T::ObjectType;

    public:
        auto IndexBegin() const -> std::size_t { return 0; }
        auto IndexEnd() const -> std::size_t { return This()->IndexEnd(); }
        auto GetObj(SizeType n) const -> ObjectType const& { return This()->GetObj(n); }
        auto GetObj(SizeType n) -> ObjectType& { return This()->GetObj(n); }
    };

    template<typename T>
    struct ScopedFooInterface : FooInterface<T> {
        using FooInterface<T>::This;
        using BitMap = typename T::BitMap;

        auto GetScope() const -> BitMap {
            return This()->GetScope();
        }
    };

    struct Foo {
        int elems[10];
        std::size_t num{};
        using BitMap = ::detail::ArrayScope<10>;

        using ElemType = int;
        using SizeType = std::size_t;
        using ObjectType = int;

        constexpr static SizeType MAX_SIZE = 10;

        using Interface = FooInterface<Foo>;

        Foo(std::initializer_list<int> list) {
            auto n = std::min(list.size(), MAX_SIZE);
            num = 0;
            for(auto&& elem : list) {
                elems[num++] = elem;
            }
        }

    public:
        auto IndexBegin() const -> std::size_t { return 0; }
        auto IndexEnd() const -> std::size_t { return num; }
        auto GetObj(SizeType n) const -> ObjectType const& { return elems[n]; }
        auto GetObj(SizeType n) -> ObjectType& { return elems[n]; }
    };

    struct ScopedFoo {
        int elems[10];
        using BitMap = ::detail::ArrayScope<10>;
        BitSet<10> scope;

        using ElemType = int;
        using SizeType = std::size_t;
        using ObjectType = int;

        constexpr static SizeType MAX_SIZE = 10;
        using Interface = ScopedFooInterface<ScopedFoo>;

    public:
        ScopedFoo(std::initializer_list<int> list) {
            auto n = std::min(list.size(), MAX_SIZE);
            auto i = 0;
            for(auto&& elem : list) {
                scope.set(i);
                elems[i++] = elem;
                if(i >= n) break;
            }
        }

    public:
        auto IndexBegin() const -> std::size_t { return 0; }
        auto IndexEnd() const -> std::size_t { return MAX_SIZE; }
        auto GetObj(SizeType n) const -> ObjectType const& { return elems[n]; }
        auto GetObj(SizeType n) -> ObjectType& { return elems[n]; }
        auto GetScope() const -> BitMap { return scope; }
    };
}

#endif //OBJECT_ARRAY_FOO_H
