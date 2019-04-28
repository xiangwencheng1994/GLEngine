#pragma once

#define SGE_PLATFORM_UNKNOWN    0
#define SGE_PLATFORM_WIN32      1
#define SGE_PLATFORM_ANDROID    2
#define SGE_PLATFORM_LINUX      3
#define SGE_PLATFORM_MAC_IOS    4

#define SGE_TARGET_PLATFORM     SGE_PLATFORM_UNKNOWN

// android
#if defined(ANDROID)
#define SGE_ANDROID
#define SGE_LINUX
#undef  SGE_TARGET_PLATFORM
#define SGE_TARGET_PLATFORM SGE_PLATFORM_ANDROID
// Win32
#elif defined(_WIN32) || defined(WIN32) || defined(_WINDOWS_)
#define SGE_WIN32
#undef  SGE_TARGET_PLATFORM
#define SGE_TARGET_PLATFORM SGE_PLATFORM_WIN32
// linux
#elif defined(LINUX) || defined(__linux__) || defined(__linux)
#define SGE_LINUX
#undef  SGE_TARGET_PLATFORM
#define SGE_TARGET_PLATFORM SGE_PLATFORM_LINUX
#endif

// setup export and inport for win32
#ifdef SGE_WIN32
#define SGE_EXPORT _declspec(dllexport)
#define SGE_IMPORT _declspec(dllimport)
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4251)
#else
#define SGE_EXPORT
#define SGE_IMPORT
#endif

#ifdef sge_EXPORTS
#define SGE_API SGE_EXPORT
#else
#define SGE_API SGE_IMPORT
#endif

// define ASSERT for debugger
#include <assert.h>
#define ASSERT(x)   assert(x)

// define disable copy object of Class
#define DISABLE_COPY(Class) \
		Class(const Class &) = delete; \
		Class &operator=(const Class &) = delete;

#define HAS_FLAG(item, flag)            ((item) & (flag))
#define ADD_FLAG(item, flag)            ((item) |= (flag))
#define REMOVE_FLAG(item, flag)         ((item) &= ~(flag))
#define SET_FLAG(item, flag, enable)    ((enable) ? ((item) |= (flag)) : ((item) &= ~(flag)))

#include <stdint.h>

typedef int32_t four_char_enum;
#define ENUM(e) enum class e : four_char_enum

//now: Use std string, vector, list, map
#include <string>
#define sgeString   std::string
#include <vector>
#define sgeVector   std::vector
#include <list>
#define sgeList     std::list
#include <map>
#define sgeMap      std::map
#define sgeMMap     std::multimap
#include <memory>
#define sgeSharedPtr    std::shared_ptr
#define sgeWeakPtr      std::weak_ptr

namespace sge
{
    namespace details
    {
        constexpr int32_t i32(const char* s, int32_t v) { return *s ? i32(s + 1, v * 256 + *s) : v; }
        constexpr uint16_t u16(const char* s, uint16_t v) { return *s ? u16(s + 1, v * 256 + *s) : v; }
        constexpr uint32_t u32(const char* s, uint32_t v) { return *s ? u32(s + 1, v * 256 + *s) : v; }
    }

    constexpr int32_t operator "" _i32(const char* s, size_t) { return details::i32(s, 0); }
    constexpr uint32_t operator "" _u32(const char* s, size_t) { return details::u32(s, 0); }
    constexpr uint16_t operator "" _u16(const char* s, size_t) { return details::u16(s, 0); }
}

