#include "utils.h"

#include "error.h"

#include <errno.h>
#include <float.h>

double
parse_double (char* start, char** end, size_t line)
{
	errno		  = 0;
	double number = strtod (start, end);
	if (start == *end)
		{
			error (ErrExpectedNumber, line);
			return 0;
		}

	if ((errno == ERANGE && number == DBL_MAX))
		{
			error (ErrExpectedNumber, line);
			return 0;
		}
	if ((errno == ERANGE && number == DBL_MIN))
		{
			error (ErrExpectedNumber, line);
			return 0;
		}

	return number;
}
