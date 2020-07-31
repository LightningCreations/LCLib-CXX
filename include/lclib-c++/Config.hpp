//
// Created by chorm on 2020-05-27.
//

#ifndef LCLIB_CONFIG_HPP
#define LCLIB_CONFIG_HPP

// Test if we have <span>
#if __cplusplus>201703L
# if __has_include(<span>)
#   define LCLIB_CXX_HAS_SPAN
# endif
#endif

#define LCLIB_CXX_EVAL0(val) val
#define LCLIB_CXX_EVAL(val) LCLIB_CXX_EVAL0(val)
#define LCLIB_CXX_QUOTE0(val) #val
#define LCLIB_CXX_QUOTE(val) LCLIB_CXX_QUOTE0(val)
#define LCLIB_CXX_PRAGMA(cmd) _Pragma(LCLIB_CXX_QUOTE(cmd))

#if defined(__linux__)
#define LCLIB_CXX_PLATFORM_LINUX
#define LCLIB_OS_NAME "lcnix"
#define LCLIB_CXX_POSIX
#elif defined(_WIN32)
#define LCLIB_CXX_PLATFORM_WINDOWS
#define LCLIB_HOST_NAME "windows"
#define LCLIB_CXX_DLL_EXPORT __declspec(dllexport)
#define LCLIB_CXX_DLL_IMPORT __declspec(dllimport)
#endif
#if defined(__GNUC__)||defined(__clang__)||defined(_LCCC_CXX)
#define LCLIB_CXX_HAS_GNU
#define LCLIB_CXX_UNREACHABLE() __builtin_unreachable()
#define LCLIB_CXX_WARN(...) LCLIB_CXX_PRAGMA(message(#__VA_ARGS__))
#if defined(_LCCC_CXX)
#define LCLIB_CXX_HAS_LCEXT
#endif
#ifndef LCLIB_CXX_DLL_EXPORT
#define LCLIB_CXX_DLL_EXPORT __attribute__((visibility("default")))
#define LCLIB_CXX_DLL_IMPORT __attribute__((visibility("default")))
#endif
#define LCLIB_CXX_ORDER_LITTLE __ORDER_LITTLE_ENDIAN__
#define LCLIB_CXX_ORDER_BIG __ORDER_BIG_ENDIAN__
#define LCLIB_CXX_BYTE_ORDER __BYTE_ORDER__
#elif defined(_MSC_VER)
#define LCLIB_CXX_HAS_MSVC
#define LCLIB_CXX_CXX_MAYBE_BROKEN
// Yes I have a sense of humor
#define LCLIB_CXX_ORDER_LITTLE 0
#define LCLIB_CXX_ORDER_BIG 1
#define LCLIB_CXX_BYTE_ORDER 0
#define LCLIB_CXX_WARN(...) LCLIB_CXX_PRAGMA(message(#__VA_ARGS__))
#define LCLIB_CXX_UNREACHABLE() (void)(*((int*)0))
#endif

#if defined(LCLIB_CXX_BUILD)
#define LCLIB_CXX_API LCLIB_CXX_DLL_EXPORT
#else
#define LCLIB_CXX_API LCLIB_CXX_DLL_IMPORT
#endif

#if !defined(LCLIB_CXX_CXX_MAYBE_BROKEN)
#if __cplusplus<201703L
#error LCLib-C++ Requires C++17 or higher
#endif
#else
LCLIB_CXX_WARN(C++ Compiler Version checks are not supported on MSVC, Things may break);
#endif

#if __cplusplus>201703L
#if __has_include(<version>)
#include <version>
#endif
#endif

#if defined(__cpp_impl_three_way_comparison)&&__cpp_impl_three_way_comparison>=201907L
#if __has_include(<compare>)
#define LCLIB_CXX_HAS_20_SPACESHIP
#endif
#endif


#endif //LCLIB_CONFIG_HPP
