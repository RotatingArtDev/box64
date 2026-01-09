#ifndef __CORE_H
#define __CORE_H

#include "custommem.h"
#include "callback.h"
#include "library.h"

// When building as a shared library, explicitly export these functions
#ifdef BOX64_AS_LIB
    #define BOX64_EXPORT __attribute__((visibility("default")))
#else
    #define BOX64_EXPORT
#endif

// exec : 0 = lib, 1 = exec
BOX64_EXPORT int initialize(int argc, const char **argv, char** env, x64emu_t** emulator, elfheader_t** elfheader, int exec);

BOX64_EXPORT int emulate(x64emu_t* emu, elfheader_t* elf_header);

int unittest(int argc, const char** argv);

#endif // __CORE_H