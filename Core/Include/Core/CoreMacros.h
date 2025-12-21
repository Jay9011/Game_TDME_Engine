#pragma once

// ==============================================================
// 컴파일러 감지
// ==============================================================

#if defined(_MSC_VER)
    #define TDME_COMPILER_MSVC 1
#elif defined(__clang__)
    #define TDME_COMPILER_CLANG 1
#elif defined(__GNUC__)
    #define TDME_COMPILER_GCC 1
#else
    #define TDME_COMPILER_UNKNOWN 1
#endif

// ==============================================================
// 플랫폼 감지
// ==============================================================

#if defined(_WIN32) || defined(_WIN64)
    #define TDME_PLATFORM_WINDOWS 1
#elif defined(__APPLE__)
    #include <TargetConditionals.h>
    #if TARGET_OS_MAC
        #define TDME_PLATFORM_MAC 1
    #endif
#elif defined(__linux__)
    #define TDME_PLATFORM_LINUX 1
#endif

#ifndef TDME_PLATFORM_WINDOWS
    #define TDME_PLATFORM_WINDOWS 0
#endif
#ifndef TDME_PLATFORM_MAC
    #define TDME_PLATFORM_MAC 0
#endif
#ifndef TDME_PLATFORM_LINUX
    #define TDME_PLATFORM_LINUX 0
#endif

// ==============================================================
// 인라인 매크로
// ==============================================================

/**
 * @brief 표준 inline 매크로
 */
#define INLINE inline

/**
 * @brief 컴파일러에게 강제 inline 을 요청하는 매크로
 */
#if TDME_COMPILER_MSVC
    #define FORCE_INLINE __forceinline
#elif TDME_COMPILER_CLANG || TDME_COMPILER_GCC
    #define FORCE_INLINE inline __attribute__((always_inline))
#else
    #define FORCE_INLINE inline
#endif

// ==============================================================
// RESTRICT 포인터
// ==============================================================

#if TDME_COMPILER_MSVC
    #define RESTRICT __restrict
#elif TDME_COMPILER_CLANG || TDME_COMPILER_GCC
    #define RESTRICT __restrict__
#else
    #define RESTRICT
#endif