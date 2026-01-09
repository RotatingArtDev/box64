#include "core.h"

#ifdef BOX64_AS_LIB
    #define MAIN_EXPORT __attribute__((visibility("default")))
#else
    #define MAIN_EXPORT
#endif

MAIN_EXPORT int main(int argc, const char **argv, char **env) {

    x64emu_t* emu = NULL;
    elfheader_t* elf_header = NULL;
    if (initialize(argc, argv, env, &emu, &elf_header, 1)) {
        return -1;
    }

    return emulate(emu, elf_header);
}
