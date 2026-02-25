#ifndef olmo_utils_h
#define olmo_utils_h

#include "flag.h"

#include <stdio.h>
#include <stdlib.h>

#define fprintfln(file, fmt, ...) fprintf (file, fmt "\n", ##__VA_ARGS__)

#define println(fmt, ...) fprintfln (stdout, fmt, ##__VA_ARGS__)
#define eprintln(fmt, ...) fprintfln (stderr, fmt, ##__VA_ARGS__)

#define ok() exit (0)
#define fail() exit (1)

#define println_exit(fmt, ...)                                            \
	println (fmt, ##__VA_ARGS__);                                         \
	ok ()

#define eprintln_exit(fmt, ...)                                           \
	println (fmt, ##__VA_ARGS__);                                         \
	fail ()

#define error(fmt, ...) eprintln_exit ("error: " fmt, ##__VA_ARGS__)
#define warn(fmt, ...) eprintln ("warn: " fmt, ##__VA_ARGS__)
#define note(fmt, ...) println ("note: " fmt, ##__VA_ARGS__)

#define debug(...)                                                        \
	if (getflag (FlagDebug))                                              \
		{                                                                 \
			printf (##__VA_ARGS__);                                       \
		}

#define debugln(fmt, ...)                                                 \
	if (getflag (FlagDebug))                                              \
		{                                                                 \
			println (fmt, ##__VA_ARGS__);                                 \
		}

// check for unix-style os
#if !defined(_WIN32)                                                      \
	&& (defined(__unix__) || defined(__unix)                              \
		|| (defined(__APPLE__) && defined(__MACH__)))
// posix compliant
#define OLMO_UNIX
#define OLMO_USE_POSIX

#if defined(__linux) || defined(__linux__)
#define OLMO_LINUX
#endif //  defined(__linux) || defined(__linux__)

#if defined(__APPLE__) && defined(__MACH__) && defined(TARGET_OS_MAC)
#define OLMO_MACOS
#endif

#endif

#if defined(__CYGWIN__) && !defined(_WIN32)
// Cygwin POSIX under Microsoft Windows.
#define OLMO_CYGWIN
#endif

#if defined(_WIN64)
// Microsoft Windows (64-bit)
#define OLMO_WINDOWS64
#define OLMO_WINDOWS
#elif defined(_WIN32)
// Microsoft Windows (32-bit)
#define OLMO_WINDOWS32
#define OLMO_WINDOWS
#endif

#endif // !olmo_utils_h
