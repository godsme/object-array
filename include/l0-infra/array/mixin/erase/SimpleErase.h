//
// Created by Darwin Yuan on 2021/7/9.
//

#ifndef OBJECT_ARRAY_2_SIMPLEERASE_H
#define OBJECT_ARRAY_2_SIMPLEERASE_H

namespace mixin {
    template<typename T>
    class SimpleErase : public T {
        using Self = T;

    public:
        using typename Self::SizeType;

        using Self::Num;
        using Self::Destroy;
        using Self::MoveObject;

    private:
        auto DoErase(SizeType n) -> void {
            --Num();
            if (n < Num()) MoveObject(n, Num());
            Destroy(Num());
        }

    public:
        auto Erase(SizeType n) -> void {
            if(n < Num()) DoErase(n);
        }
    };
}

#endif //OBJECT_ARRAY_2_SIMPLEERASE_H
