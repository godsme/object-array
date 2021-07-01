//
// Created by Darwin Yuan on 2021/6/24.
//

#ifndef OBJECT_ARRAY_OPTYPETRAIT_H
#define OBJECT_ARRAY_OPTYPETRAIT_H

namespace _concept::detail {
    template<typename T>
    struct OpTypeTrait {
        using ObjectType = typename T::ObjectType;
        using SizeType = typename T::SizeType;

        constexpr static auto CONST_PRED = [](ObjectType const&) { };
        constexpr static auto CONST_INDEX_PRED = [](ObjectType const&, SizeType) { };
        constexpr static auto PRED = [](ObjectType&) { };
        constexpr static auto INDEX_PRED = [](ObjectType&, SizeType) { };

        constexpr static auto BOOL_CONST_PRED = [](ObjectType const&) { return false; };
        constexpr static auto BOOL_CONST_INDEX_PRED = [](ObjectType const&, SizeType) { return false; };
        constexpr static auto BOOL_PRED = [](ObjectType&) { return true; };
        constexpr static auto BOOL_INDEX_PRED = [](ObjectType&, SizeType) { return true; };

        constexpr static auto STATUS_CONST_PRED = [](ObjectType const&) -> unsigned int { return 0; };
        constexpr static auto STATUS_CONST_INDEX_PRED = [](ObjectType const&, SizeType) -> unsigned int { return 7; };
        constexpr static auto STATUS_PRED = [](ObjectType&) -> unsigned int { return 10; };
        constexpr static auto STATUS_INDEX_PRED = [](ObjectType&, SizeType) -> unsigned int { return 20; };
    };
}

#endif //OBJECT_ARRAY_OPTYPETRAIT_H
