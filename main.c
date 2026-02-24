#include "flag.h"

#include <getopt.h>

flag_t flags = 0;

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
