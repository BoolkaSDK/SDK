#include <stdint.h>
#include <boolka.hpp>

#ifdef WIN32
#include <MinHook.h>
#endif

#ifdef ANDROID
#include <dlfcn.h>
#include <dobby.h>
#endif

#include "gd.h"
#include "hooks.hpp"

void Boolka::CreateFunctionHook(uintptr_t offset, const char* symbol, void* function, void** original)
{
#ifdef WIN32
    MH_CreateHook((void*)(gd::base + offset), function, original);
#endif

#ifdef ANDROID
    DobbyHook(dlsym(dlopen("libcocos2dcpp.so", RTLD_LAZY), symbol), function, original);
#endif
}

#ifdef WIN32
void Boolka::Main(HMODULE hModule)
{
    DisableThreadLibraryCalls(hModule);
    MH_Initialize();

    Hooks::init();

    MH_EnableHook(MH_ALL_HOOKS);
}
#endif

#ifdef ANDROID
void Boolka::Main()
{
    Hooks::init();
}
#endif