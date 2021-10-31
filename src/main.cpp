#include <includes.h>
#include <hooks.hpp>

#ifdef WIN32
BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        CreateThread(0, 0x1000, (LPTHREAD_START_ROUTINE)Boolka::Main, hModule, 0, 0);
    }

    return true;
}
#endif

#ifdef ANDROID
__attribute__((constructor)) void BoolkaInit()
{
    Boolka::Main();
}
#endif