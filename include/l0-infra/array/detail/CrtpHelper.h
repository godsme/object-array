//
// Created by Darwin Yuan on 2021/6/23.
//

#ifndef OBJECT_ARRAY_CRTPHELPER_H
#define OBJECT_ARRAY_CRTPHELPER_H

#define dEcL_tHiS(type) \
auto This() const -> type const* { return reinterpret_cast<type const*>(this); } \
auto This() -> type* { return reinterpret_cast<type*>(this); }

#endif //OBJECT_ARRAY_CRTPHELPER_H
