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
    DobbyHook(dlsym(gd::base, symbol), function, original);
#endif
}

#ifdef WIN32
void __stdcall Boolka::Main(HMODULE hModule)
{
    DisableThreadLibraryCalls(hModule);

#ifdef _DEBUG
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
#endif

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