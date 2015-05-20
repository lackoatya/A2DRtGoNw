#ifndef ENGINE_DEFINES_H_
#define ENGINE_DEFINES_H_

// Platform Identification
// Reference: http://sourceforge.net/p/predef/wiki/OperatingSystems/
#ifdef _WIN64
#define PLATFORM_WINDOWS_64
#elif _WIN32
#define PLATFORM_WINDOWS_32
// TODO not proper here!
#define _WIN32_WINNT 0x0501
#elif __APPLE__ && TARGET_OS_OSX 1
#define PLATFORM_OSX
#elif __linux
#define PLATFORM_LINUX
#elif __unix
#define PLATFORM_UNIX 
#elif __posix
#define PLATFORM_POSIX
#else
#define PLATFORM_UNKNOWN
#endif

// Configuration
#ifdef _DEBUG
#define CONFIGURATION_DEBUG
#endif

#endif