//
// Created by Darwin Yuan on 2021/6/29.
//

#ifndef OBJECT_ARRAY_VIEWEDARRAY_H
#define OBJECT_ARRAY_VIEWEDARRAY_H

namespace mixin {
    template<typename T>
    class ViewedArray : public T {
        using Self = T;

    protected:
        using typename T::DataHolder;
        using ArrayType = typename DataHolder::ArrayType;

    public:
        auto GetArray() -> ArrayType& {
            return reinterpret_cast<DataHolder&>(*this).GetArray();
        }
    };
}

#endif //OBJECT_ARRAY_VIEWEDARRAY_H
