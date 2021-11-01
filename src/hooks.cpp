#include <hooks.hpp>

#include <hooks/MenuLayer.hpp>

void Hooks::init()
{
    Boolka::CreateFunctionHook(
        0x1907b0, "_ZN9MenuLayer4initEv",
        (void*)Hooks::MenuLayer::init,
        (void**)&Hooks::MenuLayer::init_O);

#ifdef ANDROID
    BoolkaMemory::WriteMemory(0x65CEB2, "Boolka SDK!");  // replacing Normal Mode text
#endif

#ifdef WIN32
    BoolkaMemory::WriteMemory(0x2B12F0, "Boolka SDK!");  // replacing Normal Mode text
#endif
}