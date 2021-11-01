#include <corecrt_memcpy_s.h>
#include <stdint.h>
#include <string.h>
#include <memory.hpp>

#ifdef ANDROID
// From KittyMemory: https://github.com/MJx0/KittyMemory
bool BoolkaMemory::Protect(uintptr_t addr, size_t length, int protection)
{
    uintptr_t pageStart = _PAGE_START_OF_(addr);
    uintptr_t pageLen = _PAGE_LEN_OF_(addr, length);

    return (mprotect(reinterpret_cast<void*>(pageStart), pageLen, protection) != -1);
}
#endif

bool BoolkaMemory::WriteMemory(uintptr_t addr, u_char data)
{
#ifdef ANDROID
    addr = FindLibrary("libcocos2dcpp.so") + addr;

    if (!Protect(addr, sizeof(data), _PROT_RWX_))
        return false;

    if (memcpy((void*)addr, &data, sizeof(data)) != NULL && Protect(addr, sizeof(data), _PROT_RX_))
        return true;

    return false;
#endif

#ifdef WIN32
    addr = gd::base + addr;

    DWORD oldProtect, newProtect;
    VirtualProtect((void*)addr, sizeof(data), PAGE_EXECUTE_READWRITE, &oldProtect);
    *(DWORD*)addr = data;
    VirtualProtect((void*)addr, sizeof(data), oldProtect, &newProtect);

    return true;
#endif
}

bool BoolkaMemory::WriteMemory(uintptr_t addr, const char* buffer)
{
#ifdef ANDROID
    addr = FindLibrary("libcocos2dcpp.so") + addr;

    if (!Protect(addr, strlen(buffer), _PROT_RWX_))
        return false;

    if (memcpy((void*)addr, buffer, strlen(buffer)) != NULL && Protect(addr, strlen(buffer), _PROT_RX_))
        return true;

    return false;
#endif

#ifdef WIN32
    addr = gd::base + addr;

    DWORD oldProtect, newProtect;
    VirtualProtect((void*)addr, 1, PAGE_EXECUTE_READWRITE, &oldProtect);

    memcpy_s((void*)addr, strlen(buffer), buffer, strlen(buffer));

    VirtualProtect((void*)addr, 1, oldProtect, &newProtect);

    return true;
#endif
}

#ifdef ANDROID
uintptr_t BoolkaMemory::FindLibrary(const char* library)
{
    char filename[0xFF] = {0},
         buffer[1024] = {0};
    FILE* fp = NULL;
    uintptr_t address = 0;

    sprintf(filename, "/proc/self/maps");

    fp = fopen(filename, "rt");
    if (fp == NULL)
    {
        perror("fopen");
        if (fp)
            fclose(fp);
    }

    while (fgets(buffer, sizeof(buffer), fp))
    {
        if (strstr(buffer, library))
        {
            address = (uintptr_t)strtoul(buffer, NULL, 16);
            if (fp)
                fclose(fp);
        }
    }

    return address;
}
#endif