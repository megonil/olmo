#include "array.h"

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void*
array_init (size_t itemsize, size_t capacity)
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
array_resize (void* array, size_t n)
{
	if (len (array) + n > cap (array))
		{
			void* newarray
				= array_init (array_itemsize (array), cap (array) * 2);

			memcpy (newarray, array, len (array));
			array_free (array);
			return newarray;
		}
	else
		{
			return array;
		}
}

void
array_print (void* array, PrintFunction fn)
{
	foreach (array, i)
		{
			fn (array + i * array_itemsize (array));
		}
}

inline void
array_free (void* array)
{
	assert (array != NULL);

	free (array_header (array));
	array = NULL;
}
