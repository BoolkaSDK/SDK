#ifndef __BOOLKA_H__
#define __BOOLKA_H__

#include <includes.h>
#include "memory.hpp"

class Boolka
{
public:
#ifdef WIN32
    static void Main(HMODULE hModule);
#endif

#ifdef ANDROID
    static void Main();
#endif

    static void CreateFunctionHook(uintptr_t offset, const char* symbol, void* function, void** original);

    // TODO: static void CreateJump(uintptr_t offset, uintptr_t destination);
};

#endif  // __BOOLKA_H__