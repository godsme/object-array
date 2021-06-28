//
// Created by Darwin Yuan on 2021/6/29.
//

#ifndef OBJECT_ARRAY_INDICESBASEDSORT_H
#define OBJECT_ARRAY_INDICESBASEDSORT_H

#include <l0-infra/array/concept/Less.h>
#include <l0-infra/array/view/OrderedView.h>
#include <type_traits>
#include <algorithm>

namespace mixin {
    template<typename T>
    struct IndicesBasedSort : T {
        using Self = T;

    public:
        using typename Self::ObjectType;
        using typename Self::SizeType;

    protected:
        using typename Self::Owner;

        using Self::IndicesSort;
        using Self::IndicesStableSort;
        using Self::IndicesPartialSort;

    public:
        template<__lEsS_cOnCePt(LESS)>
        auto DoPartialSort(LESS&& less, SizeType n) & -> SizeType {
            return IndicesPartialSort(std::forward<LESS>(less), n);
        }

        template<__lEsS_cOnCePt(LESS)>
        auto Sort(LESS&& less) && -> Owner {
            IndicesSort(std::forward<LESS>(less));
            return reinterpret_cast<Owner&>(*this);
        }

        template<__lEsS_cOnCePt(LESS)>
        auto Sort(LESS&& less) & -> Owner& {
            IndicesSort(std::forward<LESS>(less));
            return reinterpret_cast<Owner&>(*this);
        }

        template<__lEsS_cOnCePt(LESS)>
        auto StableSort(LESS&& less) && -> Owner {
            IndicesStableSort(std::forward<LESS>(less));
            return reinterpret_cast<Owner&>(*this);
        }

        template<__lEsS_cOnCePt(LESS)>
        auto StableSort(LESS&& less) & -> Owner& {
            IndicesStableSort(std::forward<LESS>(less));
            return reinterpret_cast<Owner&>(*this);
        }

        template<__lEsS_cOnCePt(LESS)>
        auto PartialSort(LESS&& less, SizeType n) & -> Owner& {
            IndicesPartialSort(std::forward<LESS>(less), n);
            return reinterpret_cast<Owner&>(*this);
        }

        template<__lEsS_cOnCePt(LESS)>
        auto PartialSort(LESS&& less, SizeType n) && -> Owner {
            IndicesPartialSort(std::forward<LESS>(less), n);
            return reinterpret_cast<Owner&>(*this);
        }
    };
}

#endif //OBJECT_ARRAY_INDICESBASEDSORT_H
