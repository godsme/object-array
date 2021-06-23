//
// Created by Darwin Yuan on 2021/6/23.
//

#ifndef OBJECT_ARRAY_ARRAYCOMPOSER_H
#define OBJECT_ARRAY_ARRAYCOMPOSER_H

namespace detail {
    template<typename HOLDER, template <typename> typename MIXINS>
    class ArrayComposer : protected HOLDER, protected MIXINS<HOLDER> {
        static auto __sEcReAtE_vAliD_cHeCkEr() { static_assert(sizeof(HOLDER) == sizeof(ArrayComposer)); }
        static_assert(std::is_empty_v<MIXINS<HOLDER>>);
    public:
        using Holder = HOLDER;
        using Mixins = MIXINS<HOLDER>;
        using Holder::Holder;

        using SizeType = typename Holder::SizeType;
        using ObjectType = typename Holder::ObjectType;
    };
}

#endif //OBJECT_ARRAY_ARRAYCOMPOSER_H
