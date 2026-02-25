#include "utils.h"

#include <errno.h>
#include <float.h>

double
parse_double (char* start, char** end)
{
	errno		  = 0;
	double number = strtod (start, end);
	if (start == *end)
		{
			error ("expected number");
		}

	if ((errno == ERANGE && number == DBL_MAX))
		{
			error ("unable to parser number");
		}
	if ((errno == ERANGE && number == DBL_MIN))
		{
			error ("unable to parser number");
		}

	return number;
}
