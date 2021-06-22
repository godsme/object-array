//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_FOO_H
#define OBJECT_ARRAY_FOO_H

#include <cstddef>

namespace ut {
    template<typename T>
    class FooConcept {
        auto This() const -> T const* {
            auto* p = reinterpret_cast<T const*>(this);
            return p;
        }

    public:
        using SizeType = typename T::SizeType;
        using ObjectType = typename T::ObjectType;;

    public:
        auto IndexBegin() const -> std::size_t { return 0; }
        auto IndexEnd() const -> std::size_t { return This()->IndexEnd(); }
        auto GetObj(SizeType n) const -> ObjectType const& { return This()->GetObj(n); }
    };

    struct Foo {
        int elems[10];
        std::size_t num{};

        using ElemType = int;
        using SizeType = std::size_t;
        using ObjectType = int;

        using Concept = FooConcept<Foo>;

    public:
        auto IndexBegin() const -> std::size_t { return 0; }
        auto IndexEnd() const -> std::size_t { return num; }
        auto GetObj(SizeType n) const -> ObjectType const& { return elems[n]; }
    };
}

#endif //OBJECT_ARRAY_FOO_H
