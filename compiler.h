#ifndef COMPILER_H
#define COMPILER_H

/* -------------------------------------------------------------------------
   1. TYPE DEFINITIONS
   ------------------------------------------------------------------------- */
typedef signed int         q1616_t;
typedef signed char        int8_t;
typedef short              int16_t;
typedef signed int         int32_t;
typedef long long          int64_t;
typedef unsigned char      uint8_t;
typedef unsigned short     uint16_t;
typedef unsigned int       uint32_t;
typedef unsigned long long uint64_t;

/* -------------------------------------------------------------------------
   2. PLATFORM DETECTION & SYSTEM HEADERS
   ------------------------------------------------------------------------- */
#if defined(_WIN32) || defined(_WIN64)
    #define PLATFORM_WINDOWS 1
    #ifndef WIN32_LEAN_AND_MEAN
        #define WIN32_LEAN_AND_MEAN
    #endif
    #include <windows.h>
#else
    #define PLATFORM_LINUX 1
#endif

/* -------------------------------------------------------------------------
   3. SIMD & INTRINSICS
   ------------------------------------------------------------------------- */
#if defined(_MSC_VER)
    #include <intrin.h>
    #include <immintrin.h>
#elif defined(__GNUC__) || defined(__clang__)
    #include <x86intrin.h>
    #include <cpuid.h> /* Necessary for __cpuid_count on some GCC/Clang distros */
#endif

/* -------------------------------------------------------------------------
   4. COMPILER ABSTRACTION MACROS
   ------------------------------------------------------------------------- */
#if defined(_MSC_VER)
    /* --- Microsoft Visual C++ OR Clang-cl --- */
    #define FORCED_INLINE  __forceinline
    #define STATIC_INLINE  static __inline
    #define ALIGN32_BEG    __declspec(align(32))
    #define ALIGN32_END 

    #ifndef __clang__
        #pragma comment(lib, "kernel32.lib")
        #pragma comment(lib, "user32.lib")
        #pragma comment(lib, "gdi32.lib")
        #pragma function(memset, memcpy, memmove, memcmp)
    #endif
    
    #if !defined(_FLTUSED_DEFINED)
    #define _FLTUSED_DEFINED
        static int _fltused = 0;
    #endif

#elif defined(__GNUC__) || defined(__clang__)
    /* --- GCC / Clang (MinGW/Linux) --- */
    #define FORCED_INLINE  __attribute__((always_inline)) static __inline__
    #define STATIC_INLINE  static __inline__
    #define ALIGN32_BEG 
    #define ALIGN32_END    __attribute__((aligned(32)))

#else
    #define FORCED_INLINE  static
    #define STATIC_INLINE  static
    #define ALIGN32_BEG
    #define ALIGN32_END
#endif

/* -------------------------------------------------------------------------
   5. FEATURE DETECTION
   ------------------------------------------------------------------------- */
#if defined(__AVX2__) || defined(_M_AVX2)
    #define HAS_AVX2_SUPPORT 1
#else
    #define HAS_AVX2_SUPPORT 0
    #pragma message("COMPILER: AVX2 hardware acceleration disabled.")
#endif

/**
 * @brief Checks if the current CPU supports AVX2 at runtime.
 */
STATIC_INLINE int sys_supports_avx2(void) {
    int cpu_info[4];
#if defined(_MSC_VER)
    __cpuid(cpu_info, 7); 
#elif defined(__GNUC__) || defined(__clang__)
    /* Using the standard __cpuid_count macro from cpuid.h */
    __cpuid_count(7, 0, cpu_info[0], cpu_info[1], cpu_info[2], cpu_info[3]);
#else
    return 0;
#endif
    /* AVX2 is bit 5 of EBX (index 1) */
    return (cpu_info[1] & (1 << 5)) != 0;
}

#endif /* COMPILER_H */
