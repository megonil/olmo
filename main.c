#include <getopt.h>
#include <stdio.h>

typedef enum
{
	FlagDebug, // -d (verbose mode)
	FlagDry,   // -n (no run)
} Flag;

typedef int flag_t;

flag_t flags = 0;

#define getflag(fl) flags & (1 << fl)
#define setflag(fl) flags |= (1 << fl)

int
main (int argc, char* argv[])
{
	char c;
	while ((c = getopt (argc, argv, "d::n::")) != -1)
		{
			switch (c)
				{
				case 'd': setflag (FlagDebug); break;
				case 'n': setflag (FlagDry); break;
				}
		}

	if (optind == argc)
		{
		}

	return 0;
}
