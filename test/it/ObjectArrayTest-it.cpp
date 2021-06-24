//
// Created by Darwin Yuan on 2021/6/23.
//
#include <object-array/ObjectArray.h>
#include <experimental/type_traits>
#include <boost/ut.hpp>

using namespace boost::ut;

namespace {
    struct Foo {
        Foo(int a) : a{a} {}
        Foo(Foo const&) = default;
        ~Foo() {}

        auto operator==(Foo const&) const -> bool = default;

        int a;
    };

    using FooArray = ObjectArray<Foo, 10>;
}

template<typename ARRAY>
auto ObjectArray_SimpleFindTest(ARRAY&& array) {
    test("should be able to find the index of an existent elem") = [&] {
        auto found = array.FindIndex(Foo{3});
        expect(found.has_value());
        expect(*found == 2);
    };

    "should be able to find an existent elem"_test = [&] {
        auto* found = array.Find(Foo{3});
        expect(found != nullptr);
        expect(*found == 3);
    };

    "should return nullptr if trying to find a non-existent elem"_test = [&] {
        expect(nullptr == array.Find(Foo{0}));
    };

    "should be able to find the index of an existent elem by predicate"_test = [&] {
        auto found = array.FindIndex([](auto&& elem) {
            return elem == 3;
        });
        expect(found.has_value());
        expect(*found == 2);
    };

    "should be able to find an existent elem by predicate"_test = [&] {
        auto* found = array.Find([](auto&& elem) {
            return elem == 5;
        });
        expect(found != nullptr);
        expect(*found == 5);
    };

    "should return nullptr if trying to find a non-existent elem by predicate"_test = [&] {
        expect(nullptr == array.Find([](auto&& elem) {
            return elem == 10;
        }));
    };

    "should return std::nullopt if trying to find the index of a non-existent elem"_test = [&] {
        expect(array.FindIndex(Foo{0}) == std::nullopt);
    };

    "should return std::nullopt if trying to find the index of a non-existent elem by predicate"_test = [&] {
        expect(std::nullopt == array.FindIndex([](auto&& elem) { return elem.a == 0; }));
    };

    "should be able to know the existence of an elem"_test = [&] {
        expect(array.Exists(5));
        expect(!array.Exists(10));
    };

    "should be able to find in scope"_test = [&] {
        auto* found = array.Find(0x30, 5);
        expect(found != nullptr);
        expect(found->a == 5);
    };

    "should be able to find the index of existent elem in scope"_test = [&] {
        auto found = array.FindIndex(0x30, 5);
        expect(found.has_value());
        expect(*found == 4);
    };

    "should return true if trying to get the existent of an existent elem in scope"_test = [&] {
        expect(array.Exists(0x30, 5));
    };

    "should return false if trying to get the existent of a non-existent elem in scope"_test = [&] {
        expect(!array.Exists(0x30, 2));
    };

    "should return nullptr if out of scope"_test = [&] {
        expect(nullptr == array.Find(0x30, 2));
    };

    "should return nullopt if trying to find the index of elem out of scope"_test = [&] {
        expect(std::nullopt == array.FindIndex(0x30, 2));
    };
}

suite ObjectArraySimpleFind_Suite = [] {
    FooArray const array{{1},{2},{3},{4},{5},{6}};
    ObjectArray_SimpleFindTest(array);
    ObjectArray_SimpleFindTest(FooArray{{1},{2},{3},{4},{5},{6}});
};

template<typename ARRAY>
auto ObjectArray_RangeForTest(ARRAY&& array) {
    "should be able to iterator all items"_test = [&] {
        auto n=0;
        auto sum = 0;
        for(auto&& item : array) {
            ++n;
            sum += item.a;
        }

        expect(n == 6);
        expect(sum == (1 + 2 + 3 + 4 + 5 + 6));
    };

    "should be able to iterator all items with index"_test = [&] {
        auto n=0;
        auto sum = 0;
        for(auto&& [item, i] : array.WithIndex()) {
            expect(n == i);
            ++n;
            sum += item.a;
        }

        expect(n == 6);
        expect(sum == (1 + 2 + 3 + 4 + 5 + 6));
    };

    "range for index should not be able to modify"_test = [&] {
        for(auto&& [item, i] : array.WithIndex()) {
            static_assert(std::is_const_v<decltype(i)>);
        }
    };

    "range for index should not be able to modify if array is const"_test = [&] {
        if constexpr(std::is_const_v<std::remove_reference_t<decltype(array)>>) {
            for(auto&& [item, i] : array.WithIndex()) {
                static_assert(std::is_reference_v<decltype(item)>);
                static_assert(std::is_const_v<std::remove_reference_t<decltype(item)>>);
            }
        }
    };

    "range for index should be able to modify if array is not const"_test = [&] {
        if constexpr(!std::is_const_v<std::remove_reference_t<decltype(array)>>) {
            for(auto&& [item, i] : array.WithIndex()) {
                static_assert(std::is_reference_v<decltype(item)>);
                expect(!std::is_const_v<std::remove_reference_t<decltype(item)>>);
            }
        }
    };
}

suite ObjectArrayRangeFor_Suite = [] {
    FooArray const array{{1},{2},{3},{4},{5},{6}};
    ObjectArray_RangeForTest(array);
    ObjectArray_RangeForTest(FooArray{{1},{2},{3},{4},{5},{6}});
};

template<typename ARRAY>
auto ObjectArray_SliceTest(ARRAY&& array) {
    "should be able to find the index of an existent elem"_test = [&] {
        auto found = array.Slice(1, -2).FindIndex(Foo{3});
        expect(found.has_value());
        expect(*found == 2);
    };

    "should return nullopt if trying to find the index of a existent but not-in-range elem"_test = [&] {
        expect(!array.Slice(1, -2).FindIndex(Foo{6}));
    };

    "should be able to find the index of an existent elem in From slice"_test = [&] {
        auto found = array.From(1).FindIndex(Foo{3});
        expect(found.has_value());
        expect(*found == 2);
    };

    "should return nullopt if trying to find the index of a existent but not-in-range elem in From Slice"_test = [&] {
        expect(!array.From(1).FindIndex(Foo{1}));
    };

    "should be able to find the index of an existent elem in Until slice"_test = [&] {
        auto found = array.Until(-2).FindIndex(Foo{3});
        expect(found.has_value());
        expect(*found == 2);
    };

    "should return nullopt if trying to find the index of a existent but not-in-range elem in Until slice"_test = [&] {
        expect(!array.Until(-2).FindIndex(Foo{6}));
    };

    "should be able to rang-for"_test = [&] {
        auto n=0;
        auto sum = 0;
        for(auto&& item : array.Slice(1, -2)) {
            ++n;
            sum += item.a;
        }

        expect(n == 4);
        expect(sum == (2 + 3 + 4 + 5));
    };

    "should be able to rang-for (From)"_test = [&] {
        auto n=0;
        auto sum = 0;
        for(auto&& item : array.From(1)) {
            ++n;
            sum += item.a;
        }

        expect(n == 5);
        expect(sum == (2 + 3 + 4 + 5 + 6));
    };

    "should be able to rang-for (Until)"_test = [&] {
        auto n=0;
        auto sum = 0;
        for(auto&& item : array.Until(-2)) {
            ++n;
            sum += item.a;
        }
        expect(n == 5);
        expect(sum == (1 + 2 + 3 + 4 + 5));
    };

    "range for index should not be able to modify"_test = [&] {
        for(auto&& [item, i] : array.Slice(1, 2).WithIndex()) {
            static_assert(std::is_const_v<decltype(i)>);
        }
    };

    "range for index should not be able to modify if array is const"_test = [&] {
        if constexpr(std::is_const_v<std::remove_reference_t<decltype(array)>>) {
            for(auto&& item : array.Slice(1, -2)) {
                static_assert(std::is_reference_v<decltype(item)>);
                static_assert(std::is_const_v<std::remove_reference_t<decltype(item)>>);
            }
        }
    };

    "range for index should be able to modify if array is not const"_test = [&] {
        if constexpr(!std::is_const_v<std::remove_reference_t<decltype(array)>>) {
            for(auto&& item : array.Slice(1, -2)) {
                static_assert(std::is_reference_v<decltype(item)>);
                expect(!std::is_const_v<std::remove_reference_t<decltype(item)>>);
            }
        }
    };

    "range for item should not be able to modify if array is const"_test = [&] {
        if constexpr(std::is_const_v<std::remove_reference_t<decltype(array)>>) {
            for(auto&& [item, i] : array.Slice(1, -2).WithIndex()) {
                static_assert(std::is_reference_v<decltype(item)>);
                static_assert(std::is_const_v<std::remove_reference_t<decltype(item)>>);
            }
        }
    };

    "range for item should be able to modify if array is not const"_test = [&] {
        if constexpr(!std::is_const_v<std::remove_reference_t<decltype(array)>>) {
            for(auto&& [item, i] : array.Slice(1, -2).WithIndex()) {
                static_assert(std::is_reference_v<decltype(item)>);
                expect(!std::is_const_v<std::remove_reference_t<decltype(item)>>);
            }
        }
    };

    "should be able to access by index"_test = [&] {
        expect(array[0] == 1);
        expect(array[1] == 2);
        expect(array[2] == 3);
        expect(array[3] == 4);
        expect(array[4] == 5);
        expect(array[5] == 6);
    };

    "should be able to access by At"_test = [&] {
        auto* p = array.At(2);
        expect(p != nullptr);
        expect(*p == 3);

        if constexpr(std::is_const_v<std::remove_reference_t<decltype(array)>>) {
            expect(std::is_const_v<std::remove_pointer_t<decltype(p)>>);
        } else {
            expect(!std::is_const_v<std::remove_pointer_t<decltype(p)>>);
        }
    };

    "should return nullptr if index is out of range"_test = [&] {
        expect(array.At(6) == nullptr);
    };

    "non-const access should be able to modify"_test = [&] {
        if constexpr(!std::is_const_v<std::remove_reference_t<decltype(array)>>) {
            static_assert(std::is_reference_v<decltype(array[0])>);
            expect(!std::is_const_v<std::remove_reference_t<decltype(array[0])>>);
        }
    };

    "const access should not be able to modify"_test = [&] {
        if constexpr(std::is_const_v<std::remove_reference_t<decltype(array)>>) {
            static_assert(std::is_reference_v<decltype(array[0])>);
            expect(std::is_const_v<std::remove_reference_t<decltype(array[0])>>);
        }
    };
}

suite ObjectArraySlice_Suite = [] {
    FooArray const array{{1},{2},{3},{4},{5},{6}};
    ObjectArray_SliceTest(array);
    ObjectArray_SliceTest(FooArray{{1},{2},{3},{4},{5},{6}});
};

suite RValue_ObjectArraySlice_Suite = [] {
    "r-value object array should not be able to range for with index"_test = [] {
        static_assert(std::is_void_v<decltype(std::declval<FooArray&&>().WithIndex())>);
        static_assert(std::is_void_v<decltype(std::declval<FooArray const&&>().WithIndex())>);
        static_assert(!std::is_void_v<decltype(std::declval<FooArray&>().WithIndex())>);
        static_assert(!std::is_void_v<decltype(std::declval<FooArray const&>().WithIndex())>);
    };

    "l-value object array should be able to range for with indexed slice"_test = [] {
        static_assert(!std::is_void_v<decltype(std::declval<FooArray&>().Slice(1,2).WithIndex())>);
        static_assert(!std::is_void_v<decltype(std::declval<FooArray const&>().Slice(1,2).WithIndex())>);
    };

    "l-value object array should be able to range for with indexed scope"_test = [] {
        static_assert(!std::is_void_v<decltype(std::declval<FooArray&>().Slice(1,2).Scope(1).WithIndex())>);
        static_assert(!std::is_void_v<decltype(std::declval<FooArray const&>().Slice(1,2).Scope(1).WithIndex())>);
    };

    "r-value object array should not be able to create slice"_test = [] {
        static_assert(std::is_void_v<decltype(std::declval<FooArray&&>().Slice(1, -2))>);
        static_assert(std::is_void_v<decltype(std::declval<FooArray const&&>().Slice(1, -2))>);
        static_assert(!std::is_void_v<decltype(std::declval<FooArray&>().Slice(1, -2))>);
        static_assert(!std::is_void_v<decltype(std::declval<FooArray const&>().Slice(1, -2))>);
    };

    "r-value object array should not be able to create Scope"_test = [] {
        static_assert(std::is_void_v<decltype(std::declval<FooArray&&>().Scope(1))>);
        static_assert(std::is_void_v<decltype(std::declval<FooArray const&&>().Scope(1))>);
        static_assert(!std::is_void_v<decltype(std::declval<FooArray&>().Scope(1))>);
        static_assert(!std::is_void_v<decltype(std::declval<FooArray const&>().Scope(1))>);
    };
};

template<typename SLICE>
auto ObjectArray_SliceOpTest(SLICE&& slice) {
    "should be able to access by operator[]"_test = [&] {
        expect(slice[0] ==  2);
        expect(slice[1] ==  3);
    };

    "should be able to access by At"_test = [&] {
        auto* p = slice.At(3);
        expect(p != nullptr);
        expect(*p == 5);
    };

    "should return nullptr if index out of range"_test = [&] {
        expect(nullptr == slice.At(4));
    };

    "should be able to range for"_test = [&] {
        auto sum = 0;
        auto n = 0;
        for(auto&& elem : slice) {
            ++n;
            sum += elem.a;
        }
        expect(n == 4);
        expect(sum == 2 + 3 + 4 + 5);
    };

    "should be able to range for with index"_test = [&] {
        auto sum = 0;
        auto n = 0;
        auto index_sum = 0;
        for(auto&& [elem, i] : slice.WithIndex()) {
            ++n;
            sum += elem.a;
            index_sum += i;
        }
        expect(n == 4);
        expect(index_sum == 1 + 2 + 3 + 4);
        expect(sum == 2 + 3 + 4 + 5);
    };

    "should be find the index of an elem in range, but the index should be an array index"_test = [&] {
        auto index = slice.FindIndex(5);
        expect(index.has_value());
        expect(*index == 4);
    };

    "should be find the index of an elem in range with scope, but the index should be an array index"_test = [&] {
        auto index = slice.FindIndex(0x31, 5);
        expect(index.has_value());
        expect(*index == 4);
    };

    "should return nullopt if trying to find an out-of-range elem"_test = [&] {
        expect(!slice.FindIndex(6).has_value());
    };

    "should return nullopt if trying to find an out-of-range elem with scope"_test = [&] {
        expect(!slice.FindIndex(0x31, 3).has_value());
    };

    "should return nullopt if trying to find an out-of-range elem with scope"_test = [&] {
        auto index = slice.FindIndexEx(0x31, 3);
        expect(index.has_value());
        expect(*index == 2);
    };

    "should be able to find an elem in range"_test = [&] {
        auto* found = slice.Find(5);
        expect(found != nullptr);
        expect(*found == 5);
    };

    "should be able to find an elem in range with scope"_test = [&] {
        auto* found = slice.Find(0x31, 5);
        expect(found != nullptr);
        expect(*found == 5);
    };

    "should return nullptr if trying to find an out-of-range elem with excluded scope"_test = [&] {
        expect(nullptr == slice.FindEx(0x31, 5));
    };

    "should return nullptr if trying to find an out-of-range elem"_test = [&] {
        expect(nullptr == slice.Find(6));
    };

    "should return nullptr if trying to find an out-of-range elem with scope"_test = [&] {
        expect(nullptr == slice.Find(0x31, 4));
    };

    "should return nullptr if trying to find an out-of-range elem with scope"_test = [&] {
        auto* found = slice.FindEx(0x31, 4);
        expect(found != nullptr);
        expect(*found == 4);
    };

    "should be able to know the existent of an elem"_test = [&] {
        expect(slice.Exists(5));
        expect(!slice.Exists(6));
    };

    "should be able to know the existent of an elem with scope"_test = [&] {
        expect(slice.Exists(0x31, 5));
        expect(!slice.Exists(0x31, 3));
    };

    "should be able to know the existent of an elem with exluded scope"_test = [&] {
        expect(!slice.ExistsEx(0x31, 5));
        expect(slice.ExistsEx(0x31, 3));
    };
}

suite ObjectArraySliceView_Suite = [] {
    FooArray const array{{1}, {2}, {3}, {4}, {5}, {6}};
    ObjectArray_SliceOpTest(array.Slice(1, -2));

    FooArray array2{{1}, {2}, {3}, {4}, {5}, {6}};
    ObjectArray_SliceOpTest(array2.Slice(1, -2));
};

suite ObjectArrayFromSliceView_Suite = [] {
    FooArray const array{{1}, {2}, {3}, {4}, {5}, {6}};
    auto&& slice = array.From(1);

    "should be able to access by operator[]"_test = [&] {
        expect(slice[0] ==  2);
        expect(slice[1] ==  3);
    };

    "should be able to access by At"_test = [&] {
        auto* p = slice.At(3);
        expect(p != nullptr);
        expect(*p == 5);
    };

    "should return nullptr if index out of range"_test = [&] {
        expect(nullptr == slice.At(5));
    };

    "should be able to range for"_test = [&] {
        auto sum = 0;
        auto n = 0;
        for(auto&& elem : slice) {
            ++n;
            sum += elem.a;
        }
        expect(n == 5);
        expect(sum == 2 + 3 + 4 + 5 + 6);
    };

    "should be able to range for with index"_test = [&] {
        auto sum = 0;
        auto n = 0;
        auto index_sum = 0;
        for(auto&& [elem, i] : slice.WithIndex()) {
            ++n;
            sum += elem.a;
            index_sum += i;
        }
        expect(n == 5);
        expect(index_sum == 1 + 2 + 3 + 4 + 5);
        expect(sum == 2 + 3 + 4 + 5 + 6);
    };

    "should be find the index of an elem in range, but the index should be an array index"_test = [&] {
        auto index = slice.FindIndex(5);
        expect(index.has_value());
        expect(*index == 4);
    };

    "should be find the index of an elem in range with scope, but the index should be an array index"_test = [&] {
        auto index = slice.FindIndex(0x31, 5);
        expect(index.has_value());
        expect(*index == 4);
    };

    "should return nullopt if trying to find an out-of-range elem"_test = [&] {
        expect(!slice.FindIndex(0).has_value());
    };

    "should return nullopt if trying to find an out-of-range elem with scope"_test = [&] {
        expect(!slice.FindIndex(0x31, 3).has_value());
    };

    "should return nullopt if trying to find an out-of-range elem with scope"_test = [&] {
        auto index = slice.FindIndexEx(0x31, 3);
        expect(index.has_value());
        expect(*index == 2);
    };

    "should be able to find an elem in range"_test = [&] {
        auto* found = slice.Find(5);
        expect(found != nullptr);
        expect(*found == 5);
    };

    "should be able to find an elem in range with scope"_test = [&] {
        auto* found = slice.Find(0x31, 5);
        expect(found != nullptr);
        expect(*found == 5);
    };

    "should return nullptr if trying to find an out-of-range elem with excluded scope"_test = [&] {
        expect(nullptr == slice.FindEx(0x31, 5));
    };

    "should return nullptr if trying to find an out-of-range elem"_test = [&] {
        expect(nullptr == slice.Find(0));
    };

    "should return nullptr if trying to find an out-of-range elem with scope"_test = [&] {
        expect(nullptr == slice.Find(0x31, 4));
    };

    "should return nullptr if trying to find an out-of-range elem with scope"_test = [&] {
        auto* found = slice.FindEx(0x31, 4);
        expect(found != nullptr);
        expect(*found == 4);
    };

    "should be able to know the existent of an elem"_test = [&] {
        expect(slice.Exists(5));
        expect(!slice.Exists(1));
    };

    "should be able to know the existent of an elem with scope"_test = [&] {
        expect(slice.Exists(0x31, 5));
        expect(!slice.Exists(0x31, 3));
    };

    "should be able to know the existent of an elem with excluded scope"_test = [&] {
        expect(!slice.ExistsEx(0x31, 5));
        expect(slice.ExistsEx(0x31, 3));
    };
};

suite ObjectArrayUntilSliceView_Suite = [] {
    FooArray const array{{1}, {2}, {3}, {4}, {5}, {6}};
    auto&& slice = array.Until(-2);

    "should be able to access by operator[]"_test = [&] {
        expect(slice[0] ==  1);
        expect(slice[1] ==  2);
    };

    "should be able to access by At"_test = [&] {
        auto* p = slice.At(3);
        expect(p != nullptr);
        expect(*p == 4);
    };

    "should return nullptr if index out of range"_test = [&] {
        expect(nullptr == slice.At(5));
    };

    "should be able to range for"_test = [&] {
        auto sum = 0;
        auto n = 0;
        for(auto&& elem : slice) {
            ++n;
            sum += elem.a;
        }
        expect(n == 5);
        expect(sum == 1 + 2 + 3 + 4 + 5);
    };

    "should be able to range for with index"_test = [&] {
        auto sum = 0;
        auto n = 0;
        auto index_sum = 0;
        for(auto&& [elem, i] : slice.WithIndex()) {
            ++n;
            sum += elem.a;
            index_sum += i;
        }
        expect(n == 5);
        expect(index_sum == 0 + 1 + 2 + 3 + 4);
        expect(sum == 1 + 2 + 3 + 4 + 5);
    };

    "should be find the index of an elem in range, but the index should be an array index"_test = [&] {
        auto index = slice.FindIndex(5);
        expect(index.has_value());
        expect(*index == 4);
    };

    "should be find the index of an elem in range with scope, but the index should be an array index"_test = [&] {
        auto index = slice.FindIndex(0x31, 5);
        expect(index.has_value());
        expect(*index == 4);
    };

    "should return nullopt if trying to find an out-of-range elem"_test = [&] {
        expect(!slice.FindIndex(6).has_value());
    };

    "should return nullopt if trying to find an out-of-range elem with scope"_test = [&] {
        expect(!slice.FindIndex(0x31, 3).has_value());
    };

    "should return nullopt if trying to find an out-of-range elem with scope"_test = [&] {
        auto index = slice.FindIndexEx(0x31, 3);
        expect(index.has_value());
        expect(*index == 2);
    };

    "should be able to find an elem in range"_test = [&] {
        auto* found = slice.Find(5);
        expect(found != nullptr);
        expect(*found == 5);
    };

    "should be able to find an elem in range with scope"_test = [&] {
        auto* found = slice.Find(0x31, 5);
        expect(found != nullptr);
        expect(*found == 5);
    };

    "should return nullptr if trying to find an out-of-range elem with excluded scope"_test = [&] {
        expect(nullptr == slice.FindEx(0x31, 6));
    };

    "should return nullptr if trying to find an out-of-range elem"_test = [&] {
        expect(nullptr == slice.Find(6));
    };

    "should return nullptr if trying to find an out-of-range elem with scope"_test = [&] {
        expect(nullptr == slice.Find(0x31, 4));
    };

    "should return nullptr if trying to find an out-of-range elem with scope"_test = [&] {
        auto* found = slice.FindEx(0x31, 4);
        expect(found != nullptr);
        expect(*found == 4);
    };

    "should be able to know the existent of an elem"_test = [&] {
        expect(slice.Exists(5));
        expect(!slice.Exists(6));
    };

    "should be able to know the existent of an elem with scope"_test = [&] {
        expect(slice.Exists(0x31, 5));
        expect(!slice.Exists(0x31, 3));
    };

    "should be able to know the existent of an elem with excluded scope"_test = [&] {
        expect(!slice.ExistsEx(0x31, 5));
        expect(slice.ExistsEx(0x31, 3));
    };

    "should be able to know the num"_test = [&] {
        expect(slice.GetNum() == 5);
        expect(array.Slice(10, -2).GetNum() == 0);
        expect(array.From(10).GetNum() == 0);
        expect(array.Until(-10).GetNum() == 0);
    };

    "should be able to know if there is any elems"_test = [&] {
        expect(slice.Any());
        expect(!slice.None());
        expect(array.Slice(10, -2).None());
        expect(!array.Slice(10, -2).Any());
        expect(array.From(10).None());
    };
};

template<typename SCOPE>
auto ObjectArray_ScopeTest(SCOPE&& scope) {
    "should be able to access by operator[]"_test = [&] {
        expect(scope[0] == 1);
        expect(scope[3] == 4);
    };

    "should be able to access by At"_test = [&] {
        auto* p = scope.At(0);
        expect(p != nullptr);
        expect(*p == 1);
    };

    "should return nullptr if trying to access an out-of-scope elem by At"_test = [&] {
        expect(nullptr == scope.At(2));
    };

    "should be able to range for"_test = [&] {
        auto sum = 0;
        auto n = 0;
        for(auto&& elem : scope) {
            ++n;
            sum += elem.a;
        }
        expect(n == 3);
        expect(sum == 1 + 2 + 5);
    };

    "should be able to range for with index"_test = [&] {
        auto sum = 0;
        auto n = 0;
        auto index_sum = 0;
        for(auto&& [elem, i] : scope.WithIndex()) {
            ++n;
            sum += elem.a;
            index_sum += i;
        }
        expect(n == 3);
        expect(sum == 1 + 2 + 5);
        expect(index_sum == 0 + 1 + 4);
    };

    "should be find the index of an elem in range, but the index should be an array index"_test = [&] {
        auto index = scope.FindIndex(5);
        expect(index.has_value());
        expect(*index == 4);
    };

    "should return nullopt if trying to find an out-of-range elem"_test = [&] {
        expect(!scope.FindIndex(3).has_value());
    };

    "should be able to find an elem in range"_test = [&] {
        auto* found = scope.Find(5);
        expect(found != nullptr);
        expect(*found == 5);
    };

    "should return nullptr if trying to find an out-of-range elem"_test = [&] {
        expect(nullptr == scope.Find(3));
    };

    "should be able to know the existent of an elem"_test = [&] {
        expect(scope.Exists(5));
        expect(!scope.Exists(3));
    };
}

suite ObjectArraySliceScopedView_Suite = [] {
    FooArray const array{{1},{2},{3},{4},{5},{6}};
    ObjectArray_ScopeTest(array.Scope(0x13));
    ObjectArray_ScopeTest(array.Slice(0, -1).Scope(0x13));

    FooArray array1{{1},{2},{3},{4},{5},{6}};
    ObjectArray_ScopeTest(array1.Scope(0x13));
    ObjectArray_ScopeTest(array1.Slice(0, -1).Scope(0x13));
};


