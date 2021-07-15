//
// Created by Darwin Yuan on 2021/7/12.
//

#ifndef OBJECT_ARRAY_2_906E3003F8C0430E9059A29A73E37BC2
#define OBJECT_ARRAY_2_906E3003F8C0430E9059A29A73E37BC2

#include <cstddef>
#include <iterator>

namespace iterator {
    template<typename ARRAY>
    struct IndicesRandomIterator {
        using SizeType = typename ARRAY::SizeType;
        using ObjectType = typename ARRAY::ObjectType;

        using difference_type = std::ptrdiff_t;
        using value_type = ObjectType;
        using pointer = ObjectType*;
        using reference = ObjectType&;
        using iterator_category = std::random_access_iterator_tag;

        IndicesRandomIterator(SizeType* p, ARRAY& array) : p{p}, array{array} {}
        IndicesRandomIterator(IndicesRandomIterator const& rhs) : p{rhs.p}, array{rhs.array} {}

        auto operator=(IndicesRandomIterator const& rhs) -> IndicesRandomIterator& {
            p = rhs.p;
            array = rhs.array;
            return *this;
        }

        auto operator++() -> IndicesRandomIterator& {
            ++p;
            return *this;
        }

        auto operator--() -> IndicesRandomIterator& {
            --p;
            return *this;
        }

        auto operator++(int) -> IndicesRandomIterator {
            auto* r = p;
            ++p;
            return {r, array};
        }

        auto operator--(int) -> IndicesRandomIterator {
            auto* r = p;
            --p;
            return {r, array};
        }

        auto operator+(SizeType n) const -> IndicesRandomIterator {
            return {p + n, array};
        }

        auto operator+=(SizeType n) -> IndicesRandomIterator& {
            p += n;
            return *this;
        }

        auto operator-(SizeType n) const -> IndicesRandomIterator {
            return {p - n, array};
        }

        auto operator-=(SizeType n) const -> IndicesRandomIterator& {
            p -= n;
            return *this;
        }

        auto operator-(IndicesRandomIterator const& rhs) const -> SizeType {
            return p - rhs.p;
        }

        auto operator*() -> ObjectType& {
            return array.GetObject(*p);
        }

        auto operator[](SizeType n) -> ObjectType& {
            return array.GetObject(*(p + n));
        }

        auto operator==(IndicesRandomIterator const& rhs) const -> bool {
            return p == rhs.p;
        }

        auto operator!=(IndicesRandomIterator const& rhs) const -> bool {
            return p != rhs.p;
        }

        auto operator>=(IndicesRandomIterator const& rhs) const -> bool {
            return p >= rhs.p;
        }

        auto operator<(IndicesRandomIterator const& rhs) const -> bool {
            return p < rhs.p;
        }

        auto operator>(IndicesRandomIterator const& rhs) const -> bool {
            return p > rhs.p;
        }
    private:
        SizeType *p;
        ARRAY& array;
    };
}

#endif //OBJECT_ARRAY_2_906E3003F8C0430E9059A29A73E37BC2
