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

        constexpr static auto STATUS_CONST_PRED = [](ObjectType const&) -> uint32_t { return 0; };
        constexpr static auto STATUS_CONST_INDEX_PRED = [](ObjectType const&, SizeType) -> uint32_t { return 7; };
        constexpr static auto STATUS_PRED = [](ObjectType&) -> uint32_t { return 10; };
        constexpr static auto STATUS_INDEX_PRED = [](ObjectType&, SizeType) -> uint32_t { return 20; };

        using ConstPredType = decltype(CONST_PRED);
        using ConstIndexPredType = decltype(CONST_INDEX_PRED);
        using PredType = decltype(PRED);
        using IndexPredType = decltype(INDEX_PRED);

        using BoolConstPredType = decltype(BOOL_CONST_PRED);
        using BoolConstIndexPredType = decltype(BOOL_CONST_INDEX_PRED);
        using BoolPredType = decltype(BOOL_PRED);
        using BoolIndexPredType = decltype(BOOL_INDEX_PRED);

        using StatusConstPredType = decltype(STATUS_CONST_PRED);
        using StatusConstIndexPredType = decltype(STATUS_CONST_INDEX_PRED);
        using StatusPredType = decltype(STATUS_PRED);
        using StatusIndexPredType = decltype(STATUS_INDEX_PRED);
    };
}

#endif //OBJECT_ARRAY_OPTYPETRAIT_H
