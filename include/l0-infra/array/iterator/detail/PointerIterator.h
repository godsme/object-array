//
// Created by Darwin Yuan on 2021/7/12.
//

#ifndef OBJECT_ARRAY_2_777CB4A6632E41E3B749D15531E18AEF
#define OBJECT_ARRAY_2_777CB4A6632E41E3B749D15531E18AEF

namespace iterator::detail {
    template<typename T>
    struct PointerIterator {
        PointerIterator(T *p) : p{p} {}

        auto operator!=(PointerIterator const &rhs) const -> bool { return p != rhs.p; }

    protected:
        auto StepForward() -> void { ++p; }
        auto GetValue() const -> T const& { return *p; }
        auto GetValue() -> T& { return *p; }

    protected:
        T *p;
    };
}

#endif //OBJECT_ARRAY_2_777CB4A6632E41E3B749D15531E18AEF
