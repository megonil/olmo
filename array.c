#include "array.h"

#include "utils.h"

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void*
ArrayInit (size_t itemsize, size_t capacity)
{
	size_t size = itemsize * capacity;
	size += sizeof (ArrayHeader);

	ArrayHeader* header = calloc (1, size);

	if (!header)
		{
			error ("unable to allocate header");
		}

	header->cap		 = capacity;
	header->len		 = 0;
	header->itemsize = itemsize;

	return header + 1;
}

void*
ArrayResize (void* array, size_t n)
{
	if (Len (array) + n > Cap (array))
		{
			void* newarray
				= ArrayInit (ArrayItemsize (array), Cap (array) * 2);

			memcpy (newarray, array, Len (array));
			ArrayFree (array);
			return newarray;
		}
	else
		{
			return array;
		}
}

void
ArrayPrint (void* array, PrintFunction fn)
{
	foreach (array, i)
		{
			fn (array + i * ArrayItemsize (array));
		}
}

inline void
ArrayFree (void* array)
{
	assert (array != NULL);

	free (ArrayH (array));
}
