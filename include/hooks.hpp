#ifndef __HOOKS_H__
#define __HOOKS_H__

#include <boolka.hpp>
#include "includes.h"

#ifdef WIN32
#define CREATE_HOOK(name, type, selftype, ...)                     \
    inline type(__thiscall* name##_O)(selftype self, __VA_ARGS__); \
    type __fastcall name(selftype self, int, __VA_ARGS__);
#endif

#ifdef ANDROID
#define CREATE_HOOK(name, type, selftype, ...)             \
    inline type (*name##_O)(selftype self, ##__VA_ARGS__); \
    type name(selftype self, int, ##__VA_ARGS__);
#endif

namespace Hooks
{
    void init();
}

#endif  // __HOOKS_H__