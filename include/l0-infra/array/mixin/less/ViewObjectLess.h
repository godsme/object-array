//
// Created by Darwin Yuan on 2021/7/13.
//

#ifndef OBJECT_ARRAY_2_615CD906FE554D5CB4E41EA65D16128E
#define OBJECT_ARRAY_2_615CD906FE554D5CB4E41EA65D16128E


namespace mixin {
    template<typename T>
    struct ViewObjectLess : T {
        auto GetLess() const -> decltype(auto) {
            return T::GetArray().GetLess();
        }
    };
}

#endif //OBJECT_ARRAY_2_615CD906FE554D5CB4E41EA65D16128E
