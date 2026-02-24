#ifndef olmo_utils_h
#define olmo_utils_h

#include "flag.h"

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

#endif // !olmo_utils_h
