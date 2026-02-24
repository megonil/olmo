#ifndef olmo_flag_h
#define olmo_flag_h

typedef enum
{
	FlagDebug, // -d (verbose mode)
	FlagDry,   // -n (no run)
} Flag;

typedef int flag_t;

extern flag_t flags;

#define getflag(fl) flags & (1 << fl)
#define setflag(fl) flags |= (1 << fl)

#endif // !olmo_flag_h
