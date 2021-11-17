#include <corecrt_memcpy_s.h>
#include <stdint.h>
#include <string.h>
#include <memory.hpp>

#ifdef ANDROID
BoolkaMemory::base = BoolkaMemory::FindLibrary("libcocos2dcpp.so");

// From KittyMemory: https://github.com/MJx0/KittyMemory
bool BoolkaMemory::Protect(uintptr_t addr, size_t length, int protection)
{
    uintptr_t pageStart = _PAGE_START_OF_(addr);
    uintptr_t pageLen = _PAGE_LEN_OF_(addr, length);

    return (mprotect(reinterpret_cast<void*>(pageStart), pageLen, protection) != -1);
}
#endif

bool BoolkaMemory::WriteMemory(uintptr_t offset, const char* buffer)
{
#ifdef ANDROID
    uintptr_t addr = base + offset;

    if (!Protect(addr, strlen(buffer), _PROT_RWX_))
        return false;

    if (memcpy((void*)addr, buffer, strlen(buffer)) != NULL && Protect(addr, strlen(buffer), _PROT_RX_))
        return true;

    return false;
#endif

#ifdef WIN32
    uintptr_t addr = gd::base + offset;

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