/* Include BOX64_DLSYM macro from wrappedlib_init.h */
#ifndef BOX64_DLSYM
#ifdef __ANDROID__
typedef void* (*glibc_bridge_dlsym_fn)(void* handle, const char* symbol);
extern glibc_bridge_dlsym_fn box64_glibc_bridge_dlsym_hook;
static inline void* box64_native_dlsym_cb(void* handle, const char* symbol) {
    if (box64_glibc_bridge_dlsym_hook) {
        return box64_glibc_bridge_dlsym_hook(handle, symbol);
    }
    return dlsym(handle, symbol);
}
#define BOX64_DLSYM(handle, symbol) box64_native_dlsym_cb(handle, symbol)
#else
#define BOX64_DLSYM(handle, symbol) dlsym(handle, symbol)
#endif
#endif

#define TYPENAME3(N,M) N##M
#define TYPENAME2(N,M) TYPENAME3(N,M)
#define TYPENAME(N) TYPENAME2(LIBNAME, _my_t)

typedef struct TYPENAME2(LIBNAME, _my_s) {
    // functions
    #define GO(A, B)    B   A;
    SUPER()
    #undef GO
    #ifdef ADDED_STRUCT
    ADDED_STRUCT()
    #endif
} TYPENAME(LIBNAME);

static library_t* my_lib = NULL;
static TYPENAME(LIBNAME) TYPENAME2(my_, LIBNAME) = {0};
static TYPENAME(LIBNAME) * const my = &TYPENAME2(my_, LIBNAME);

static void getMy(library_t* lib)
{
    #define GO(A, W) my->A = (W)BOX64_DLSYM(lib->w.lib, #A);
    SUPER()
    #undef GO
    my_lib = lib;
    #ifdef ADDED_INIT
    ADDED_INIT()
    #endif
}

static void freeMy()
{
    #ifdef ADDED_FINI
    ADDED_FINI()
    #endif
    my_lib = NULL;
}

#define HAS_MY

#ifndef ADDED_SUPER
#undef SUPER
#endif
