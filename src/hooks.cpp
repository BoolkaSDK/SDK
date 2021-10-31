#include <hooks.hpp>

#include <hooks/MenuLayer.hpp>

void Hooks::init()
{
    Boolka::CreateFunctionHook(
        0x1907b0, "_ZN9MenuLayer4initEv",
        (void*)Hooks::MenuLayer::init,
        (void**)&Hooks::MenuLayer::init_O);
}