#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <includes.h>

#ifdef ANDROID
#include <sys/mman.h>
#include <unistd.h>

// From KittyMemory: https://github.com/MJx0/KittyMemory
#define _SYS_PAGE_SIZE_ (sysconf(_SC_PAGE_SIZE))

#define _PAGE_START_OF_(x) ((uintptr_t)x & ~(uintptr_t)(_SYS_PAGE_SIZE_ - 1))
#define _PAGE_END_OF_(x, len) (_PAGE_START_OF_((uintptr_t)x + len - 1))
#define _PAGE_LEN_OF_(x, len) (_PAGE_END_OF_(x, len) - _PAGE_START_OF_(x) + _SYS_PAGE_SIZE_)
#define _PAGE_OFFSET_OF_(x) ((uintptr_t)x - _PAGE_START_OF_(x))

#define _PROT_RWX_ (PROT_READ | PROT_WRITE | PROT_EXEC)
#define _PROT_RX_ (PROT_READ | PROT_EXEC)
#endif

class BoolkaMemory
{
private:
#ifdef ANDROID
    static uintptr_t base;

    static bool Protect(uintptr_t addr, size_t length, int protection);
    static uintptr_t FindLibrary(const char* library);
#endif

public:
    static bool WriteMemory(uintptr_t offset, const char* buffer);
};

#endif  // __MEMORY_H__