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


