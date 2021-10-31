#ifndef __BOOLKA_H__
#define __BOOLKA_H__

#include <includes.h>

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
};

#endif // __BOOLKA_H__