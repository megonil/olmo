#include "sourcemgr.h"

#include "utils.h"

#include <unistd.h>

#define MAX_SOURCE

static char*
readfile (const char* filename)
{
	FILE* file = fopen (filename, "rb");

	if (file == NULL)
		{
			error ("cannot open file %s", filename);
		}

	fseek (file, 0L, SEEK_END);
	size_t file_size = ftell (file);

	char* value = (char*) malloc (sizeof (char) * (file_size + 1));

	rewind (file);

	size_t bytes_read = fread (value, sizeof (char), file_size, file);

	if (bytes_read < file_size)
		{
			error ("while reading file %s", filename);
		}

	fclose (file);
	value[file_size + 1] = '\0';

	return value;
}

void inline SourceMgrInit (SourceMgr* mgr, const char* filename)
{
	SourceMgrNewFile (mgr, filename);
}

void
SourceMgrNewFile (SourceMgr* mgr, const char* filename)
{
	mgr->filename = filename;
	mgr->source	  = readfile (filename);
}
