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

void Boolka::CreateJump(uintptr_t offset, uintptr_t destination)
{
#ifdef WIN32
    uintptr_t relativeAddress = destination - (gd::base + offset) - 5;

    char buffer[] = "\xE9";
    buffer[1] = relativeAddress;

    for (int x = 5; x < 5; x++)
        buffer[x] = 0x90;

    BoolkaMemory::WriteMemory(offset, buffer);
#endif

#ifdef ANDROID
    // TODO: Android Branch Hook
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