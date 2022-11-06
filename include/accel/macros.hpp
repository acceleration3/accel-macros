#ifndef ACCEL_MACROS_H
#define ACCEL_MACROS_H

#include <cstdint>
#include <iostream>

#define MACRO_BLOCK_BEGIN do {
#define MACRO_BLOCK_END } while (0)

// Debug trap
#if defined(_MSC_VER)
    #define ACC_BREAK __debugbreak()
#elif defined(__GNUC__)
    #define ACC_BREAK __builtin_trap()
#else
    #error Compiler debug break not defined
#endif

// Debug only
#if !defined(NDEBUG) || defined(_DEBUG)
    #define ACC_DEBUG_ONLY(x) x
#else
    #define ACC_DEBUG_ONLY(x)    
#endif

// Assertions
#define ACC_ASSERT(expr)                                                                                \
ACC_DEBUG_ONLY(                                                                                         \
    MACRO_BLOCK_BEGIN                                                                                   \
        if (!(expr))                                                                                    \
        {                                                                                               \
            std::cerr << "Failed assertion: " << #expr << "\n";                                         \
            std::cerr << "Location: " << __FILE__ << "@" << __FUNCTION__ << "():" << __LINE__ << "\n";  \
            ACC_BREAK;                                                                                  \
        }                                                                                               \
    MACRO_BLOCK_END                                                                                     \
)

// Platform detection
#if defined(__MINGW32__) || defined(_MSC_VER) || defined(_WIN32) || defined(__CYGWIN__)
    #define PLATFORM_WINDOWS
#elif defined(__EMSCRIPTEN__)
    #define PLATFORM_WEB
#elif defined(__ANDROID__) || defined(ANDROID)
    #define PLATFORM_ANDROID
#elif defined(__linux__)
    #define PLATFORM_LINUX
#elif defined(__APPLE__) && defined(__MACH__)
    #include <TargetConditionals.h>
    #if TARGET_OS_IPHONE == 1
        #define PLATFORM_IOS
    #elif TARGET_OS_MAC == 1
        #define PLATFORM_MACOS
    #else
        #error Unsupported apple platform
    #endif
#else
    #error Unsupported platform
#endif

// CPU architecture detection
#if defined(__i386__) || defined(i386) || defined(_M_IX86) || defined(_X86_)
    #define ARCHITECTURE_X86
#elif defined(__x86_64__) || defined(_M_X64)
    #define ARCHITECTURE_X86_64
#elif defined(__arm64__) || defined(__aarch64__)
    #define ARCHITECTURE_ARM64
#elif defined(arm) || defined(__arm__) || defined(ARM) || defined(_ARM_)
    #define ARCHITECTURE_ARM
#endif

// Unused variable
#define ACC_UNUSED(x) (void)x

// Thread local variable
#if defined(__GNUC__)
    #define ACC_THREAD_LOCAL __thread
#elif defined(_MSC_VER)
    #define ACC_THREAD_LOCAL __declspec(thread)
#elif __STDC_VERSION__ >= 201112L
    #define ACC_THREAD_LOCAL _Thread_local
#else
    #error Compiler thread local storage keyword not defined
#endif

// Align hint
#if defined(__GNUC__)
    #define ACC_ALIGN_HINT(x) __attribute__((aligned(x)))
#elif defined(_MSC_VER)
    #define ACC_ALIGN_HINT(x) __declspec(align(x))
#else
    #error Compiler align hint not defined
#endif

// Always inline hint
#if defined(__GNUC__)
    #define ACC_INLINE_HINT __attribute__((always_inline))
#elif defined(_MSC_VER)
    #define ACC_INLINE_HINT __forceinline
#else
    #error Compiler inline hint not defined
#endif

// Export macro
#if (defined(_MSC_VER) || defined(__MINGW32__))
    #if defined(STATIC_BUILD)
        #define ACC_EXPORT
    #else
        #if defined(ACCEL_EXPORTS)
            #define ACC_EXPORT __declspec(dllexport)
        #else
            #define ACC_EXPORT __declspec(dllimport)
        #endif
    #endif
#else
    #define ACC_EXPORT __attribute__((visibility("default")))
#endif

#endif
